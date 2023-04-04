package de.vogella.android.lightsensor

import android.app.Activity
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.media.AudioManager
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import android.widget.TextView
import android.widget.ToggleButton
import de.vogella.android.lightsensor.databinding.ActivityMainBinding
import org.apache.commons.csv.CSVFormat
import org.apache.commons.csv.CSVPrinter
import java.io.File
import java.io.FileWriter


class MainActivity : Activity(), SensorEventListener {

    //CMake init
    init {
        System.loadLibrary("lightsensor")
    }

    external fun onSensorEvent(sensorValue: Float, mode: Char) : Double
    external fun startEngine()
    external fun stopEngine()
    external fun toneSet(doSound: Boolean)

    // light sensor init
    private lateinit var binding: ActivityMainBinding
    private lateinit var sensorManager: SensorManager
    private var brightness: Sensor? = null

    // light data storage
    private data class LightData(val time: Long, val lux: Float) {}
    private var dataPoints = ArrayList<LightData>()

    // flags
    var doRecord: Boolean = false
    var doSound: Boolean = false
    var outdoorMode: Boolean = false
    var mode: Char = 'I'

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)

        //toggle buttons UI
        val sensorToggle = findViewById<ToggleButton>(R.id.sensorToggleButton)
        val toneToggle = findViewById<ToggleButton>(R.id.toneToggleButton)
        val modeToggle = findViewById<ToggleButton>(R.id.modeToggleButton)

        //data store
        val file = File(filesDir,"lightdata.csv")

        Log.d("AUDIODEVICES", AudioManager.GET_DEVICES_OUTPUTS.toString())

        toneToggle.setOnClickListener {
            doSound = !doSound
        }
        modeToggle.setOnClickListener {
            outdoorMode = !outdoorMode
        }

        if (file.exists()) {
            sensorToggle.setOnClickListener {
                val csvOut = CSVPrinter(
                    FileWriter(file, true), CSVFormat.EXCEL.withSkipHeaderRecord()
                )
                doRecord = !doRecord
                dataPoints.forEach {
                    csvOut.printRecord("${it.time}", "${it.lux}")
                    csvOut.flush()
                }
                csvOut.close()
            }
        }
        else {
            file.createNewFile()
            Log.d("DEBUGDIR", file.absolutePath)

            sensorToggle.setOnClickListener {
                val csvOut = CSVPrinter(
                    FileWriter(file, true), CSVFormat.EXCEL.withSkipHeaderRecord()
                )
                doRecord = !doRecord
                dataPoints.forEach {
                    csvOut.printRecord("${it.time}", "${it.lux}")
                    csvOut.flush()
                }
                csvOut.close()
            }
        }

        sensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
        brightness = sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT)
    }

    override fun onSensorChanged(event: SensorEvent?) {
        if (event?.sensor?.type == Sensor.TYPE_LIGHT) {
            val sensorOutput = findViewById<TextView>(R.id.luxSensorText)
            val toneOutput = findViewById<TextView>(R.id.audioHzText)
            val light1 = event.values[0]
            val time = System.currentTimeMillis()
            toneSet(doSound)
            if (doSound) {
                if (!outdoorMode) {
                    toneOutput.text = onSensorEvent(light1, 'I').toString()
                }
                else {
                    toneOutput.text = onSensorEvent(light1, 'O').toString()
                }
            }
            else {
                toneOutput.text = "0.0";
            }
            sensorOutput.text = light1.toString()
            if (doRecord) {
                dataPoints.add(LightData(time, light1))
                Log.i("LIGHT", "$time | $light1 LUX")
            }
        }
    }


    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
        return
    }

    override fun onResume() {
        super.onResume()
        startEngine()
        toneSet(true)
        sensorManager.registerListener(this, brightness, SensorManager.SENSOR_DELAY_FASTEST)
    }

    override fun onPause() {
        super.onPause()
        stopEngine()
        toneSet(false)
        sensorManager.unregisterListener(this)
    }
}