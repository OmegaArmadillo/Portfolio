package com.example.gamerecommender

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    private lateinit var popularMovies: RecyclerView
    private lateinit var popularGamesAdapter: GamesAdapter
    private lateinit var popularMoviesLayoutMgr: LinearLayoutManager
    private var popularMoviesPage = 1


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        GamesRepository.getPopularMovies(onSuccess = ::onPopularMoviesFetched,
            onError = ::onError)

        popularMovies = findViewById(R.id.popular_movies)
        popularMoviesLayoutMgr = LinearLayoutManager(
            this,
            LinearLayoutManager.VERTICAL,
            false
        )
        popularMovies.layoutManager = popularMoviesLayoutMgr
        popularGamesAdapter = GamesAdapter(mutableListOf()){ movie -> showMovieDetails(movie) }

        popularMovies.adapter = popularGamesAdapter


        getPopularMovies()

        GamesRepository.getPopularMovies(
            popularMoviesPage,
            ::onPopularMoviesFetched,
            ::onError
        )

}



    private fun onError() {
        Toast.makeText(this, getString(R.string.error_fetch_games), Toast.LENGTH_SHORT).show()
    }

private fun getPopularMovies() {
    GamesRepository.getPopularMovies(
        popularMoviesPage,
        ::onPopularMoviesFetched,
        ::onError
    )
}
private fun onPopularMoviesFetched(games: List<Game>) {
    popularGamesAdapter.appendMovies(games)
    attachPopularMoviesOnScrollListener()
}
private fun attachPopularMoviesOnScrollListener() {
    popularMovies.addOnScrollListener(object : RecyclerView.OnScrollListener() {
        override fun onScrolled(recyclerView: RecyclerView, dx: Int, dy: Int) {
            val totalItemCount = popularMoviesLayoutMgr.itemCount
            val visibleItemCount = popularMoviesLayoutMgr.childCount
            val firstVisibleItem = popularMoviesLayoutMgr.findFirstVisibleItemPosition()
            if (firstVisibleItem + visibleItemCount >= totalItemCount / 2) {
                popularMovies.removeOnScrollListener(this)
                popularMoviesPage++
                getPopularMovies()
            }
        }
    })
}


private fun showMovieDetails(game: Game) {
    val intent = Intent(this, MovieDetailsActivity::class.java)
    intent.putExtra(MOVIE_BACKDROP, game.posterPath)
   // intent.putExtra(MOVIE_POSTER, game.posterPath)
    intent.putExtra(MOVIE_TITLE, game.name)
    intent.putExtra(MOVIE_RATING, game.rating)
    intent.putExtra(MOVIE_RELEASE_DATE, game.releaseDate)
    intent.putExtra(GAME_RATINGS, game.ratings)
    intent.putExtra(GAME_ADDED, game.added)
    intent.putExtra(GAME_SUGGESTED, game . sugessted)
    startActivity(intent)
    }
}


