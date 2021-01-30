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

class HammerGameActivity : AppCompatActivity(){

        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_game_hammer)

            var lastRoundInfo: GameInfo? = null

            val bundle : Bundle? = intent.extras

            bundle?.apply {

                lastRoundInfo = getSerializable("GameInfo") as GameInfo?

            }

            var hasFailed = true

            val hitAmount = 4.random() + 1

            var currentHits = 0

            val hitButton = findViewById<Button>(R.id.hitButton)

            val hitsRemainingTextBox = findViewById<TextView>(R.id.hitsRemainingTextBox)
            hitsRemainingTextBox.text=hitAmount.toString()


            val hammerSuccessTextView = findViewById<TextView>(R.id.hammerSuccessTextView)

            hitButton.setOnClickListener(View.OnClickListener {

                if(hitAmount-currentHits > 0)
                {
                    currentHits = currentHits + 1

                    hitsRemainingTextBox.text=(hitAmount-currentHits).toString()
                }


                if(currentHits >= hitAmount )
                {
                    hasFailed = false
                    hammerSuccessTextView.text = resources.getString(R.string.gameSuccess)
                }

            })


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
                            0
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