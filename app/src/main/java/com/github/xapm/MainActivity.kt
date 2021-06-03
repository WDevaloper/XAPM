package com.github.xapm

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }


    var test: Test? = null
    fun objectAlloc(view: View) {
        test = Test()
    }

    fun init(view: View) = Monitor.init("")

    fun release(view: View) = Monitor.release()

}
