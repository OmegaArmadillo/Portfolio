package com.example.gamerecommender

import com.google.gson.annotations.SerializedName

data  class  Game(
/*
    @SerializedName("age_ratings") val age_rating: Int,
    @SerializedName("cover") val cover: Int,
    @SerializedName("name") val name: String,
    @SerializedName("summary") val summary: String,
    @SerializedName("rating") val rating : Double

 */





    @SerializedName("id") val id: Long,
    @SerializedName("name") val name: String,
    @SerializedName("ratings_count") val ratings: String,
    @SerializedName("background_image") val posterPath: String,
    @SerializedName("background_image_additional") val backdropPath: String,
    @SerializedName("rating") val rating: Float,
    @SerializedName("released") val releaseDate: String,
    @SerializedName("added") val added: String,
    @SerializedName("suggestions_count") val sugessted: String





)