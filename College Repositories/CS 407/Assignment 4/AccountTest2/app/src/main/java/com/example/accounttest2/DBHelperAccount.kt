package com.example.accounttest2


import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import java.util.ArrayList

class DBHelperAccount (context: Context) : SQLiteOpenHelper(context, DBHelperAccount.DATABASE_NAME, null, DBHelperAccount.DATABASE_VERSION) {

    companion object {
        val DATABASE_VERSION = 1  // Database Version
        val DATABASE_NAME = "game_results_db_accounts" // Database Name
    }

    // Database Table Name
    private val TABLE_NAME = "resultsTable"
    // Attributes for Tables
    private val COLUMN_ID = "id"
    private val COLUMN_ACCOUNT = "account"
    private val COLUMN_PASSWORD = "difficulty"

    // Create table SQL query
    private val CREATE_TABLE = (
            "CREATE TABLE " + TABLE_NAME + "("
                    + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + COLUMN_ACCOUNT + " TEXT,"
                    + COLUMN_PASSWORD + " TEXT"
                    + ")")


    // 1) Select All Query, 2)looping through all rows and adding to list 3) close db connection, 4) return todos list
    fun allAccounts(accountName: String, accountPassword: String): ArrayList<Account> {

        val accounts = ArrayList<Account>()
        val selectQuery =
            "SELECT  * FROM " + TABLE_NAME + " WHERE " + COLUMN_ACCOUNT + " = '" + accountName + "' AND " + COLUMN_PASSWORD + " = '" + accountPassword + "' "

        val db = this.writableDatabase
        val cursor = db.rawQuery(selectQuery, null)
        if (cursor.moveToFirst()) {
            do {
                val account = Account(
                    cursor!!.getInt(cursor.getColumnIndex(COLUMN_ID)),
                    cursor.getString(cursor.getColumnIndex(COLUMN_ACCOUNT)),
                    cursor.getString(cursor.getColumnIndex(COLUMN_PASSWORD))
                )

                account.id = cursor.getInt(cursor.getColumnIndex(COLUMN_ID))
                account.accountName = cursor.getString(cursor.getColumnIndex(COLUMN_ACCOUNT))
                account.password = cursor.getString(cursor.getColumnIndex(COLUMN_PASSWORD))
                accounts.add(account)
            } while (cursor.moveToNext())


        }
        db.close()
        return accounts
    }






        // Creating Tables
        override fun onCreate(db: SQLiteDatabase) {
            db.execSQL(CREATE_TABLE)  // create notes table
        }

        // Upgrading database
        override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME) // Drop older table if existed
            onCreate(db)  // Create tables again
        }

        fun insertAccount(account: Account): Long {
            val db = this.writableDatabase   // get writable database as we want to write data
            val values = ContentValues()
            // `id` and `timestamp` will be inserted automatically, no need to add them
            values.put(COLUMN_ACCOUNT, account.accountName)
            values.put(COLUMN_PASSWORD, account.password)
            val id = db.insert(TABLE_NAME, null, values)  // insert row
            db.close() // close db connection

            return id  // return newly inserted row id
        }

/*
        fun deleteGameResult(account: Account): Boolean {
            val db = writableDatabase   // Gets the data repository in write mode
            db.delete(
                TABLE_NAME,
                COLUMN_ID + " LIKE ?",
                arrayOf(account.id.toString())
            ) // Issue SQL statement.
            return true
        }
*/


}