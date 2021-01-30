package com.example.aswitch.games

import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.view.View
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.aswitch.GameInfo
import com.example.aswitch.R
import com.example.aswitch.TransitionActivity
import java.io.Serializable

class SearchGameActivity : AppCompatActivity(){


        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_game_search)


            var lastRoundInfo: GameInfo? = null

            val bundle : Bundle? = intent.extras

            bundle?.apply {

                lastRoundInfo = getSerializable("GameInfo") as GameInfo?

            }

            var hasFailed = true

            val searchButton1 = findViewById<Button>(R.id.searchButton1)
            val searchButton2 = findViewById<Button>(R.id.searchButton2)
            val searchButton3 = findViewById<Button>(R.id.searchButton3)
            val searchButton4 = findViewById<Button>(R.id.searchButton4)
            val searchButton5 = findViewById<Button>(R.id.searchButton5)
            val searchButton6 = findViewById<Button>(R.id.searchButton6)
            val searchButton7 = findViewById<Button>(R.id.searchButton7)
            val searchButton8 = findViewById<Button>(R.id.searchButton8)
            val searchButton9 = findViewById<Button>(R.id.searchButton9)

            val buttonSelected = 8.random() + 1

            val button1 = 1
            val button2 = 2
            val button3 = 3
            val button4 = 4
            val button5 = 5
            val button6 = 6
            val button7 = 7
            val button8 = 8
            val button9 = 9


            val searchSuccessTextArea = findViewById<TextView>(R.id.searchSuccessTextArea)

            searchButton1.setOnClickListener(View.OnClickListener {

                if(button1 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton2.setOnClickListener(View.OnClickListener {

                if(button2 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton3.setOnClickListener(View.OnClickListener {

                if(button3 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton4.setOnClickListener(View.OnClickListener {

                if(button4 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton5.setOnClickListener(View.OnClickListener {

                if(button5 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton6.setOnClickListener(View.OnClickListener {

                if(button6 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton7.setOnClickListener(View.OnClickListener {

                if(button7 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton8.setOnClickListener(View.OnClickListener {

                if(button8== buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })

            searchButton9.setOnClickListener(View.OnClickListener {

                if(button9 == buttonSelected)
                {
                    hasFailed = false
                    searchSuccessTextArea.text = resources.getString(R.string.gameSuccess)
                }
                else
                {
                    searchSuccessTextArea.text = resources.getString(R.string.gameFailure)
                }


            })


           // searchButton1.setBackgroundColor(1)

            Handler().postDelayed(
                {
                    val nextIntent = Intent(this, TransitionActivity::class.java)

                    val gameInfo : GameInfo =
                        GameInfo(
                            lastRoundInfo!!.roundsSucceded,
                            lastRoundInfo!!.roundTime,
                            lastRoundInfo!!.difficulty,
                            hasFailed,
                            lastRoundInfo!!.roundsFailed,
                            lastRoundInfo!!.failMaximum,
                            2
                        )

                    nextIntent.putExtra("GameInfo", gameInfo as Serializable)

                    startActivity(nextIntent)
                    finish()
                }, lastRoundInfo!!.roundTime.toLong() * 1000
            )

        }

    fun Int.random(): Int {

        //create a random number
        return (0..this).random()
    }


}