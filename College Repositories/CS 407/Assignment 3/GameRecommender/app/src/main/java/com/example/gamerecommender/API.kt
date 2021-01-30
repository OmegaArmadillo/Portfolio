package com.example.gamerecommender

import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Query

interface API {
    @GET("games?dates=2019-01-01,2019-12-31&ordering=-added")
    fun getPopularMovies(
       //@Query("user_key") apiKey : String = "04991790973a6f93a17814ba82469770",
       // @Query("api_key") apiKey : String = "fb6a390b7af577cb0226a1d6fb1304a3",
      // @Query("Accept") accept : String = "application/json",
        @Query("page") page : Int,
        @Query("User-Agent") agent : String = "game recommender"
       // @Query("fields") fields : String = "where game.platforms = 48 & date < 1538129354, sort date desc;"

    ) : Call<GetGamesResponse>
}