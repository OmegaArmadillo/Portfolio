package com.example.aswitch


import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.view.animation.AnimationUtils
import android.widget.ImageView
import android.widget.RatingBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.aswitch.games.HammerGameActivity
import com.example.aswitch.games.MathGameActivity
import com.example.aswitch.games.SearchGameActivity
import kotlinx.android.synthetic.main.activity_transition.*
import java.io.Serializable


class TransitionActivity : AppCompatActivity(){




    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_transition)


        var lastRoundInfo: GameInfo? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            lastRoundInfo = getSerializable("GameInfo") as GameInfo?

        }





        //set success text
        val lastRoundStateTextView = findViewById<TextView>(R.id.lastRoundStateTextView)

        if(lastRoundInfo?.failedCurrentRound == true)
        {
            lastRoundStateTextView.text=getString(R.string.transitionFailureText)
        }
        else
        {
            lastRoundStateTextView.text=getString(R.string.transitionSuccessText)
        }



        //add to rounds succeeded if won
        var currentWins = lastRoundInfo!!.roundsSucceded

        if (lastRoundInfo?.failedCurrentRound == false)
        {
            currentWins = currentWins + 1
        }



        //add to rounds failed if lost
        var currentLoses = lastRoundInfo!!.roundsFailed

        if(lastRoundInfo?.failedCurrentRound ==  true)
        {
            currentLoses = lastRoundInfo!!.roundsFailed + 1
        }


        //set the rating bar for attempts left
        val attemptsLeftBar = findViewById<RatingBar>(R.id.attemptsLeft)

        attemptsLeftBar.rating =  lastRoundInfo!!.failMaximum.toFloat() - currentLoses.toFloat()



        //figure out next round time
        val nextRoundTime = lastRoundInfo!!.roundTime * .9



        //figure out if the player should lose the game
        var hasLost = false

        if(currentLoses == lastRoundInfo?.failMaximum)
        {
            hasLost = true
        }




        //decide the next game
        val gameAmount = 3

        val gameChoice = (gameAmount-1).random()

        var nextIntent = Intent(this, MainActivity::class.java)


        when(gameChoice)
        {
            0 -> nextIntent = Intent(this, HammerGameActivity::class.java)
            1 -> nextIntent = Intent(this, MathGameActivity::class.java)
            2 -> nextIntent = Intent(this, SearchGameActivity::class.java)
            else -> nextIntent = Intent(this, MainActivity::class.java)
        }


        if(hasLost == true)
        {
            nextIntent = Intent(this, GameOverActivity::class.java)
        }






        //set the values for the images
        val image: ImageView = findViewById<ImageView>(R.id.lastGameImage)
        val image2: ImageView = findViewById<ImageView>(R.id.nextGameImage)

        when(lastRoundInfo!!.lastGame)
        {
            0 ->image.setImageResource((R.drawable.circle_hammer))
            1 ->image.setImageResource((R.drawable.circle_math))
            2 -> image.setImageResource((R.drawable.circle_search))
            else -> image.setImageResource((R.drawable.circle))
        }







        //play the animation
       Handler().postDelayed(
           {
               transitionAnimation(lastRoundInfo!!.lastGame,gameChoice,lastRoundInfo!!.roundTime.toLong() * 400, hasLost)
               image2.alpha = 1f
           }
           ,lastRoundInfo!!.roundTime.toLong() * 500)





        //go to the next activity after an amount of time
        Handler().postDelayed(
            {
                val gameInfo : GameInfo =
                    GameInfo(
                        currentWins,
                        nextRoundTime.toFloat(),
                        lastRoundInfo!!.difficulty,
                        false,
                        currentLoses,
                        lastRoundInfo!!.failMaximum,
                        -1
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




    fun transitionAnimation(lastGame:Int, nextGame:Int, animationDuration: Long, hasLost: Boolean) {
        val image: ImageView = findViewById<ImageView>(R.id.lastGameImage)
        val image2: ImageView = findViewById<ImageView>(R.id.nextGameImage)



        when(lastGame)
        {
            0 ->image.setImageResource((R.drawable.circle_hammer))
            1 ->image.setImageResource((R.drawable.circle_math))
            2 -> image.setImageResource((R.drawable.circle_search))
            else -> image.setImageResource((R.drawable.circle))
        }

        when(nextGame)
        {
            0 ->image2.setImageResource((R.drawable.circle_hammer))
            1 ->image2.setImageResource((R.drawable.circle_math))
            2 -> image2.setImageResource((R.drawable.circle_search))
            else -> image2.setImageResource((R.drawable.circle))
        }

        if(hasLost == true)
        {
            image2.setImageResource(R.drawable.circle_fail)
        }

        val animationLastGame = AnimationUtils.loadAnimation(applicationContext, R.anim.animation_move_first)
        val animationFirstGame = AnimationUtils.loadAnimation(applicationContext, R.anim.animation_move_second)

        animationLastGame.duration = animationDuration
        animationFirstGame.duration = animationDuration

        image.startAnimation(animationLastGame)
        image2.startAnimation(animationFirstGame)
    }



}