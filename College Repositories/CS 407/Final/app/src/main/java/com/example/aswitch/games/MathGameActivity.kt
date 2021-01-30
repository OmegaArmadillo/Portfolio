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

class MathGameActivity : AppCompatActivity(){
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_game_math)



        var lastRoundInfo: GameInfo? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            lastRoundInfo = getSerializable("GameInfo") as GameInfo?

        }

        var hasFailed = true

        val digits = resources.getStringArray(R.array.numbers)

        val equationTextView = findViewById<TextView>(R.id.equationTextView)

        val firstNumber = 9.random()
        val secondNumber = 9.random()

        val whichSign = 1.random()

        var numberTotal = 0


        if(whichSign == 0)
        {
            numberTotal = firstNumber + secondNumber
            equationTextView.text= "${digits[firstNumber]} ${resources.getString(R.string.mathGameAdd)} ${digits[secondNumber]}"
        }
        else
        {
            numberTotal = firstNumber - secondNumber
            equationTextView.text= "${digits[firstNumber]} ${resources.getString(R.string.mathGameSubtract)} ${digits[secondNumber]}"
        }

        val incorrectAnswer1 = numberTotal + 2
        val incorrectAnswer2 = numberTotal + 1
        val incorrectAnswer3 = numberTotal - 1

        val answerButton1 = findViewById<Button>(R.id.answerButton1)
        val answerButton2 = findViewById<Button>(R.id.answerButton2)
        val answerButton3 = findViewById<Button>(R.id.answerButton3)

        answerButton1.text = incorrectAnswer1.toString()
        answerButton2.text = incorrectAnswer2.toString()
        answerButton3.text = incorrectAnswer3.toString()

        var answer1 = incorrectAnswer1
        var answer2 = incorrectAnswer2
        var answer3 = incorrectAnswer3

        val buttonChanged = 2.random()

        if(buttonChanged == 0)
        {
            answerButton1.text=numberTotal.toString()
            answer1 = numberTotal
        }
        else if (buttonChanged == 1)
        {
            answerButton2.text=numberTotal.toString()
            answer2 = numberTotal
        }
        else
        {
            answerButton3.text=numberTotal.toString()
            answer3 = numberTotal
        }


        val equationSuccessTextView = findViewById<TextView>(R.id.equationSuccessTextView)


        answerButton1.setOnClickListener(View.OnClickListener {

           if(answer1 == numberTotal)
           {
               hasFailed = false
               equationSuccessTextView.text = resources.getString(R.string.gameSuccess)
           }
            else
           {
               equationSuccessTextView.text = resources.getString(R.string.gameFailure)
           }


        })

        answerButton2.setOnClickListener(View.OnClickListener {

            if(answer2 == numberTotal)
            {
                hasFailed = false
                equationSuccessTextView.text = resources.getString(R.string.gameSuccess)
            }
            else
            {
                equationSuccessTextView.text = resources.getString(R.string.gameFailure)
            }


        })

        answerButton3.setOnClickListener(View.OnClickListener {

            if(answer3== numberTotal)
            {
                hasFailed = false
                equationSuccessTextView.text = resources.getString(R.string.gameSuccess)
            }
            else
            {
                equationSuccessTextView.text = resources.getString(R.string.gameFailure)
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
                        1
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