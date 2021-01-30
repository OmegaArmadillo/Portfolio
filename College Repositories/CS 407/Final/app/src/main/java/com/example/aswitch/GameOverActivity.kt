package com.example.aswitch

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.aswitch.database.DBHelper
import com.example.aswitch.database.GameResult

class GameOverActivity : AppCompatActivity()  {


    private var dbHelper: DBHelper? = null



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_gameover)

        dbHelper = DBHelper(this)

        var lastRoundInfo: GameInfo? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            lastRoundInfo = getSerializable("GameInfo") as GameInfo?

        }

        val roundsWonTextView = findViewById<TextView>(R.id.roundsWonTextView)
        roundsWonTextView.text = (lastRoundInfo!!.roundsSucceded).toString()

        val resultNameTextEnter = findViewById<TextView>(R.id.resultNameTextEnter)


        val stopButton = findViewById<Button>(R.id.stopButton)
        stopButton.setOnClickListener(View.OnClickListener {


            val result: GameResult =
                GameResult(
                    resultNameTextEnter.text.toString(),
                    lastRoundInfo!!.roundsSucceded,
                    lastRoundInfo!!.difficulty
                )

            createResult(result)


            val intent : Intent = Intent(this, MainActivity::class.java)


            startActivity(intent)


        })


    }


    private fun createResult(gameResult: GameResult) {
         dbHelper!!.insertGameResult(gameResult)

    }

}