package com.example.aswitch

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ListView
import androidx.appcompat.app.AppCompatActivity
import com.example.aswitch.database.DBHelper
import com.example.aswitch.database.ResultAdapter

class LeaderboardActivity : AppCompatActivity()  {

    private lateinit var listView: ListView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_leaderboard)

         var dbHelper: DBHelper =
             DBHelper(this)
         var resultList =  dbHelper!!.allResults

        listView = findViewById<ListView>(R.id.leaderboardList)

        val adapter =
            ResultAdapter(this, resultList)
        listView.adapter = adapter


        val mainMenuButton = findViewById<Button>(R.id.mainMenuButton)
        mainMenuButton.setOnClickListener(View.OnClickListener {


            val intent : Intent = Intent(this, MainActivity::class.java)


            startActivity(intent)


        })
    }
}