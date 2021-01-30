package com.example.accounttest2


import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ListView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import java.io.Serializable


class LeaderboardActivity : AppCompatActivity()  {

    private lateinit var listView: ListView
    var dbHelper: DBHelper = DBHelper(this)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_leaderboard)

        //  var resultAdapter: ResultAdapter? = null



        var accountInfo: Account? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            accountInfo = getSerializable("AccountInfo") as Account?

        }





        //var resultList =  dbHelper!!.allResults
        var resultList = dbHelper!!.allAccountResults(accountInfo!!.accountName)

        listView = findViewById<ListView>(R.id.leaderboardList)

        val adapter = ResultAdapter(this, resultList)
        listView.adapter = adapter


        listView.setOnItemClickListener { _, _, position, _ ->
            Toast.makeText(this, "Dislike.", Toast.LENGTH_SHORT).show()

            val selectedResult = resultList[position]

            deleteResult(selectedResult)

            var resultList =  dbHelper!!.allAccountResults(accountInfo!!.accountName)

            val adapter = ResultAdapter(this, resultList)
            listView.adapter = adapter
        }


        val mainMenuButton = findViewById<Button>(R.id.mainMenuButton)

        mainMenuButton.setOnClickListener(View.OnClickListener {


            val account = Account(accountInfo!!.accountName,"")

            val intent : Intent = Intent(this, MainActivity::class.java)

            intent.putExtra("AccountInfo", account as Serializable)

            startActivity(intent)


        })
    }


    private fun deleteResult(gameResult: GameResult) {
        dbHelper!!.deleteGameResult(gameResult)   // inserting note in db and getting newly inserted note id

    }

}