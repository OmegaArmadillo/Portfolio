$('#team').change(function () {
    var team = $('#team').val();
    var source = '/SportsInfo/GetTeamAthlete?teamID=' + team;

    $.ajax({
        type: 'GET',
        dataType: 'json',
        url: source,
        success: createList,
        error: error
    });
});


function createList(data) {

    var count = data.id.length;

    var html = '<select class = "form-control" id = "player">';

    for (var i = 0; i < count; i++)
    {
        html = html + '<option value ="' + data.id[i] + '">' + data.name[i] + '</option>'
    }

    html = html + '</select>'

    $('#playerArea').html(html);

}



$('#event').change(function () {
    var player = $('#player').val();
    var event = $('#event').val();
    var source = '/SportsInfo/GetAthleteData?athleteID=' + player + '&eventID=' + event;

    $.ajax({
        type: 'GET',
        dataType: 'json',
        url: source,
        success: plotData,
        error: error
    });
});


function plotData(data) {
    
        var plotValues = {
            x: data.x,
            y: data.y,
            mode: 'lines',
            type: 'line'
        };
        console.log(data.x);
        var plotData = [plotValues];
        var layout = {};
        Plotly.newPlot('plotArea', plotData, layout);
    
}


function error() {
    console.log('The function did not run correctly');
}