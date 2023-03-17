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

    external fun onSensorEvent(sensorValue: Float);
    external fun startEngine();
    external fun stopEngine();
    external fun restartEngine();

    // light sensor init
    private lateinit var binding: ActivityMainBinding
    private lateinit var sensorManager: SensorManager
    private var brightness: Sensor? = null

    // light data storage
    private data class LightData(val time: Long, val lux: Float) {}
    private var dataPoints = ArrayList<LightData>()

    // flags
    var doRecord: Boolean = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)

        //toggle buttons UI
        val sensorToggle = findViewById<ToggleButton>(R.id.sensorToggleButton)

        //data store
        val file = File(filesDir,"lightdata.csv")

        Log.d("AUDIODEVICES", AudioManager.GET_DEVICES_OUTPUTS.toString())

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
            //Log.d("DEBUGDIR", file.absolutePath)

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
            val light1 = event.values[0]
            val time = System.currentTimeMillis()
            onSensorEvent(light1)
            sensorOutput.text = light1.toString()
            if (doRecord) {
                dataPoints.add(LightData(time, light1))
                //Log.i("LIGHT", "$time | $light1 LUX")
            }
        }
    }


    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
        return
    }

    override fun onResume() {
        super.onResume()
        restartEngine()
        sensorManager.registerListener(this, brightness, SensorManager.SENSOR_DELAY_FASTEST)
    }

    override fun onPause() {
        super.onPause()
        stopEngine()
        sensorManager.unregisterListener(this)
    }
}