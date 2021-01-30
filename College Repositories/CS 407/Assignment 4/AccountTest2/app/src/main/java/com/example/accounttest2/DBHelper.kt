package com.example.accounttest2


import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import java.util.ArrayList

class DBHelper (context: Context) : SQLiteOpenHelper(context, DBHelper.DATABASE_NAME, null, DBHelper.DATABASE_VERSION){

    companion object {
        private val DATABASE_VERSION = 1  // Database Version
        private val DATABASE_NAME = "game_results_db_account" // Database Name
    }

    // Database Table Name
    private val TABLE_NAME = "resultsTable"
    // Attributes for Tables
    private val COLUMN_ID = "id"
    private val COLUMN_PLAYER = "player"
    private val COLUMN_ROUNDS = "rounds"
    private val COLUMN_DIFFICULTY = "difficulty"
    private val COLUMN_ACCOUNT = "account"

    // Create table SQL query
    private val CREATE_TABLE = (
            "CREATE TABLE " + TABLE_NAME + "("
                    + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + COLUMN_PLAYER + " TEXT,"
                    + COLUMN_ROUNDS + " INTEGER,"
                    + COLUMN_DIFFICULTY + " TEXT,"
                    + COLUMN_ACCOUNT + " TEXT"
                    + ")")

    // 1) Select All Query, 2)looping through all rows and adding to list 3) close db connection, 4) return todos list
    val allResults : ArrayList<GameResult>
        get() {
            val results = ArrayList<GameResult>()
            val selectQuery = "SELECT  * FROM " + TABLE_NAME + " ORDER BY " + COLUMN_ROUNDS + " DESC"

            val db = this.writableDatabase
            val cursor = db.rawQuery(selectQuery, null)
            if (cursor.moveToFirst()) {
                do {
                    val result = GameResult(cursor!!.getInt(cursor.getColumnIndex(COLUMN_ID)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_PLAYER)),
                        cursor.getInt(cursor.getColumnIndex(COLUMN_ROUNDS)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_DIFFICULTY)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_ACCOUNT)))

                    result.id = cursor.getInt(cursor.getColumnIndex(COLUMN_ID))
                    result.player = cursor.getString(cursor.getColumnIndex(COLUMN_PLAYER))
                    result.rounds = cursor.getInt(cursor.getColumnIndex(COLUMN_ROUNDS))
                    result.difficulty = cursor.getString(cursor.getColumnIndex(COLUMN_DIFFICULTY))
                    results.add(result)
                } while (cursor.moveToNext())
            }
            db.close()
            return results
        }




    fun allAccountResults(accountName:String?): ArrayList<GameResult> {

            val results = ArrayList<GameResult>()
            val selectQuery =
                "SELECT  * FROM " + TABLE_NAME + " WHERE " + COLUMN_ACCOUNT + " = '" + accountName + "' ORDER BY " + COLUMN_ROUNDS + " DESC"

            val db = this.writableDatabase
            val cursor = db.rawQuery(selectQuery, null)
            if (cursor.moveToFirst()) {
                do {
                    val result = GameResult(
                        cursor!!.getInt(cursor.getColumnIndex(COLUMN_ID)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_PLAYER)),
                        cursor.getInt(cursor.getColumnIndex(COLUMN_ROUNDS)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_DIFFICULTY)),
                        cursor.getString(cursor.getColumnIndex(COLUMN_ACCOUNT))
                    )
                    result.id = cursor.getInt(cursor.getColumnIndex(COLUMN_ID))
                    result.player = cursor.getString(cursor.getColumnIndex(COLUMN_PLAYER))
                    result.rounds = cursor.getInt(cursor.getColumnIndex(COLUMN_ROUNDS))
                    result.difficulty = cursor.getString(cursor.getColumnIndex(COLUMN_DIFFICULTY))
                    result.account = cursor.getString(cursor.getColumnIndex(COLUMN_ACCOUNT))
                    results.add(result)
                } while (cursor.moveToNext())
            }
            db.close()
            return results

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

    fun insertGameResult(gameResult: GameResult): Long {
        val db = this.writableDatabase   // get writable database as we want to write data
        val values = ContentValues()
        // `id` and `timestamp` will be inserted automatically, no need to add them
        values.put(COLUMN_PLAYER, gameResult.player)
        values.put(COLUMN_ROUNDS, gameResult.rounds)
        values.put(COLUMN_DIFFICULTY, gameResult.difficulty)
        values.put(COLUMN_ACCOUNT, gameResult.account)
        val id = db.insert(TABLE_NAME, null, values)  // insert row
        db.close() // close db connection

        return id  // return newly inserted row id
    }


    fun deleteGameResult(result: GameResult): Boolean {
        val db = writableDatabase   // Gets the data repository in write mode
        db.delete(TABLE_NAME, COLUMN_ID + " LIKE ?", arrayOf(result.id.toString())) // Issue SQL statement.
        return true
    }


}