package com.example.aswitch

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.Spinner
import com.example.aswitch.games.HammerGameActivity
import com.example.aswitch.games.MathGameActivity
import com.example.aswitch.games.SearchGameActivity
import java.io.Serializable

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.main_activity)


        var selectedDifficulty = "Normal"
        var selectedTime = 5f


        val difficultySpinner = findViewById<Spinner>(R.id.difficultySpinner)
        val difficulty = resources.getStringArray(R.array.difficulty)

        val difficultySpinnerAdapter = ArrayAdapter(this, android.R.layout.simple_spinner_item, difficulty)


        difficultySpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(p0: AdapterView<*>?) {
            }

            override fun onItemSelected(p0: AdapterView<*>?, p1: View?, position: Int, p3: Long) {
                selectedDifficulty = difficulty[position]
            }

        }

        difficultySpinner.adapter=difficultySpinnerAdapter



        val startButton = findViewById<Button>(R.id.startButton)
        startButton.setOnClickListener(View.OnClickListener {


                    if(selectedDifficulty == "Easy")
                    {
                        selectedTime = 6f
                    }
                    else if (selectedDifficulty == "Hard")
                    {
                        selectedTime = 4f
                    }
                    else
                    {
                        selectedTime = 5f
                    }


                    val gameInfo : GameInfo =
                        GameInfo(
                            0,
                            selectedTime,
                            selectedDifficulty,
                            false,
                            0,
                            3,
                            -1
                        )




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

                    nextIntent.putExtra("GameInfo", gameInfo as Serializable)

                    startActivity(nextIntent)
        })


        val leaderboardButton = findViewById<Button>(R.id.leaderboardButton)
        leaderboardButton.setOnClickListener(View.OnClickListener {


            val intent : Intent = Intent(this, LeaderboardActivity::class.java)


            startActivity(intent)


        })



    }

    fun Int.random(): Int {

        //create a random number
        return (0..this).random()
    }

}
