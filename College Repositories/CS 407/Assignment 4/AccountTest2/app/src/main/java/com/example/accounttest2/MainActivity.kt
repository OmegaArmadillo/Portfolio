package com.example.accounttest2



import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ListView
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.Serializable

import java.util.ArrayList

class MainActivity : AppCompatActivity()  {

    private lateinit var listView: ListView
    var dbHelper: DBHelper = DBHelper(this)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //  var resultAdapter: ResultAdapter? = null


        var accountInfo: Account? = null

        val bundle : Bundle? = intent.extras

        bundle?.apply {

            accountInfo = getSerializable("AccountInfo") as Account?

        }




        val accountNameText = findViewById<TextView>(R.id.accountName)


        if(accountInfo != null)
        {
            accountNameText.text = accountInfo!!.accountName
        }



        var resultList =  ArrayList<GameResult>()

        resultList.add(GameResult("not me", 25, "hard",""))
        resultList.add(GameResult("possibly me", 9, "easy",""))
        resultList.add(GameResult("maybe me", 7, "normal",""))

        listView = findViewById<ListView>(R.id.leaderboardList)

        val adapter = ResultAdapter(this, resultList)
        listView.adapter = adapter


        listView.setOnItemClickListener { _, _, position, _ ->

            Toast.makeText(this, "Like.", Toast.LENGTH_SHORT).show()

            val selectedResult = resultList[position]

            selectedResult.account = accountNameText.text.toString()

            createResult(selectedResult)
        }



        val loginButton = findViewById<Button>(R.id.loginButton)
        // val context = this



        loginButton.setOnClickListener(View.OnClickListener {



            val intent : Intent = Intent(this, AccountActivity::class.java)


            startActivity(intent)


        })



        val mainMenuButton = findViewById<Button>(R.id.mainMenuButton)




        mainMenuButton.setOnClickListener(View.OnClickListener {

            val account = Account(accountNameText.text.toString(),"")

            val intent : Intent = Intent(this, LeaderboardActivity::class.java)

            intent.putExtra("AccountInfo", account as Serializable)

            startActivity(intent)


        })
    }

    private fun createResult(gameResult: GameResult) {
        dbHelper!!.insertGameResult(gameResult)    // inserting note in db and getting newly inserted note id

    }

}
