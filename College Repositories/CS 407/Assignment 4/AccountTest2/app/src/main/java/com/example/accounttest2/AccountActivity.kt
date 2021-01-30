package com.example.accounttest2

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import java.io.Serializable

class AccountActivity : AppCompatActivity() {


     var dbHelper: DBHelperAccount = DBHelperAccount(this)


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)


        val accountNameText = findViewById<TextView>(R.id.nameTextView)
        val accountPasswordText = findViewById<TextView>(R.id.passwordTextView)




        val createButton = findViewById<Button>(R.id.createAccountButton)


        createButton.setOnClickListener(View.OnClickListener {


            val account = Account(accountNameText.text.toString(), accountPasswordText.text.toString())

            var resultList =  dbHelper!!.allAccounts(accountNameText.text.toString(), accountPasswordText.text.toString())

            if(resultList.size >=1)
            {
                Toast.makeText(this, "Account Already Exists", Toast.LENGTH_SHORT).show()
            }
            else
            {
                createAccount(account)
                Toast.makeText(this, "Account Created", Toast.LENGTH_SHORT).show()
            }





        })



        val loginButton = findViewById<Button>(R.id.loginButton)


        loginButton.setOnClickListener(View.OnClickListener {


            val account = Account(accountNameText.text.toString(), accountPasswordText.text.toString())

            var resultList =  dbHelper!!.allAccounts(accountNameText.text.toString(),accountPasswordText.text.toString())



            if(resultList.size >=1)
            {
                val intent : Intent = Intent(this, MainActivity::class.java)

                intent.putExtra("AccountInfo", account as Serializable)

                startActivity(intent)

            }
            else
            {

                Toast.makeText(this, "Invalid Information", Toast.LENGTH_SHORT).show()
            }






        })




        val mainMenuButton = findViewById<Button>(R.id.mainMenuButton)

        mainMenuButton.setOnClickListener(View.OnClickListener {


            val account = Account("","")

            val intent : Intent = Intent(this, MainActivity::class.java)

            intent.putExtra("AccountInfo", account as Serializable)

            startActivity(intent)


        })




    }

    private fun createAccount(account: Account) {
        dbHelper!!.insertAccount(account)    // inserting note in db and getting newly inserted note id

    }
}