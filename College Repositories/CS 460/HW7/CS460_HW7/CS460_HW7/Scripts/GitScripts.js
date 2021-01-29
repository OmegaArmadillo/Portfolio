function getRepoCommits(user, repo)
{
    //call the controller action
    var controllerFunction = '/api/commits?user=' + user + '&repo=' + repo;

    //get the data if it succeeds otherwise run an error message
    $.ajax({
        type: 'GET',
        dataType: 'json',
        url: controllerFunction,
        success: createCommits,
        error: errorMessage
    });
}

function createCommits(commitData)
{

    console.log('data  retrieved');

    //get the length of the data
    var count = commitData.name.length;

    //wipe the data on the screen
    $('#commitArea').text("");

    //start the element that is added
    var appendData = "<table style='background-color:white'> <tr> <th>Sha</th> <th>Author</th> <th>Date</th> <th>Message</th></tr>";

    //add the data from the lists to the element
    for (var i = 0; i < count; i++)
    {
        
        appendData = appendData + "<tr>" + "<td> <a href='" + commitData.link[i] + "'>"  + commitData.sha[i] + "</a> </td><td>" + commitData.name[i] + "</td><td>" + commitData.date[i] + "</td > <td>" + commitData.message[i] + "</td></tr>";
        

    }

    //add the table end to the element
    appendData = appendData + "</table>"

    //add the data to the page
    $('#commitArea').append(appendData);
    
}

function errorMessage()
{
    console.log('there was an error getting commit data');
}