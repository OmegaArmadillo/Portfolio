
//the function that swaps between the 2d and 3d modes
function swap()
{
	//finds the value of the selected radio button
	var dimension = $('input[name="dimension"]:checked').val();
	
	//checks which dimension is selected and disables the z values if necessary
	if(dimension == 2)
	{
		$('#uZ').prop("disabled",true);
		$('#vZ').prop("disabled",true);
		console.log("2d");
	}
	else
	{
		$('#uZ').prop("disabled",false);
		$('#vZ').prop("disabled",false);
		console.log("3d");
	}
	
}

//sets the function to activate when the radio buttons are selected
$('#dimension1').click(swap);
$('#dimension2').click(swap);

//checks if the inputs are valid
function check()
{
	//stops the page from reloading
	event.preventDefault();
	
	//get the values for the u vector
	var uX = $('#uX').val();
	var uY = $('#uY').val();
	var uZ = $('#uZ').val();
	
	//gets the value for the v vector
	var vX = $('#vX').val();
	var vY = $('#vY').val();
	var vZ = $('#vZ').val();
	
	//finds the current dimension
	var dimension = $('input[name="dimension"]:checked').val();
	
	//finds the equation to be used
	var equation = $('input[name="equation"]:checked').val();
	
	//checks if the inputs for each dimension are numbers and if they are not it prints an error message, if it succeeds it calculate the values
	if(dimension == 2)
	{
		if($.isNumeric(uX) && $.isNumeric(uY) && $.isNumeric(vX) && $.isNumeric(vY))
		{
			$('#message').html("Calculating Answer.");
			
			if(equation == "dot")
			{
				calculateDot();
			}
			else
			{
				calculateCross();
			}
			
			
		}
		else
		{
			$('#message').html("All used values must be numbers in numerical form.");
		}
	}
	
	else
	{
		if($.isNumeric(uX) && $.isNumeric(uY) && $.isNumeric(uZ) && $.isNumeric(vX) && $.isNumeric(vY) && $.isNumeric(vZ))
		{
			$('#message').html("Calculating Answer.");
			
			if(equation == "dot")
			{
				calculateDot();
			}
			else
			{
				calculateCross();
			}
		}
		else
		{
			$('#message').html("All used values must be numbers in numerical form.");
		}
	}
	
}

//sets the equaiton to run when the submit button is pressed
$('#dotProduct').submit(check);

//calculates the dot product
function calculateDot()
{
	//gets the required values sets z to zero incase the 3rd dimension is not used
	var uX = $('#uX').val();
	var uY = $('#uY').val();
	var uZ = 0;
	
	var vX = $('#vX').val();
	var vY = $('#vY').val();
	var vZ = 0; 
	
	//finds the dimension
	var dimension = $('input[name="dimension"]:checked').val();

	//finds the z values in necessary
	if(dimension == 2)
	{
		uZ = 0;
		vZ = 0; 
	}
	else
	{
		uZ = $('#uZ').val();
		vZ = $('#vZ').val();
	}
	
	
	//does the calculations
	var X = uX * vX;
	var Y = uY * vY;
	var Z = uZ * vZ;
	
	var total = X + Y + Z;
		
	
	//creates a table and appends the table to the page 
	$('#answer').append(`
	<table>
	<tr>
		<th>x</th>
		<th></th>
		<th>y</th>
		<th></th>
		<th>z</th>
		<th></th>
		<th>u * v</th>
	</tr>
	
	<tr>
		<td>(` + uX + `+` + vX +  `)</td>
		<td>+</td>
		<td>(` + uY + `+` + vY +  `)</td>
		<td>+</td>
		<td>(` + uZ + `+` + vZ +  `)</td>
		<td>=</td>
		<td>u * v</td>
	</tr>
	
	<tr>
		<td>` + X + `</td>
		<td>+</td>
		<td>` + Y + `</td>
		<td>+</td>
		<td>` + Z + `</td>
		<td>=</td>
		<td>u * v</td>
	</tr>
	
	<tr>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td>` + total +`</td>
		<td>=</td>
		<td>`+ `u * v` +`</td>
	</tr>
	</table>`)
}

function calculateCross()
{
	
	//gets the required values sets z to zero incase the 3rd dimension is not used	
	var uX = $('#uX').val();
	var uY = $('#uY').val();
	var uZ = 0;
	
	var vX = $('#vX').val();
	var vY = $('#vY').val();
	var vZ = 0; 
	
	//finds the dimension
	var dimension = $('input[name="dimension"]:checked').val();
	
	//finds the z values in necessary
	if(dimension == 2)
	{
		uZ = 0;
		vZ = 0; 
	}
	else
	{
		uZ = $('#uZ').val();
		vZ = $('#vZ').val();
	}
	
	//does the calculations
	var x1 = (uY * vZ);
	var x2 = (uZ * vY);
	
	var y1 = (uZ * vX);
	var y2 = (uX * vZ)
	
	var z1 = (uX * vY);
	var z2 = (uY * vX);
	
	
	var X = (x1) - (x2);
	var Y = (y1) - (y2);
	var Z = (z1) - (z2);
	
	
	
	//creates a table and appends the table to the page 
	$('#answer').append(`
	<table>
	<tr>
		<th>x</th>
		<th></th>
		<th>y</th>
		<th></th>
		<th>z</th>
		<th></th>
		<th>`+ `u X v` +`</th>

	</tr>
	
	<tr>
		<td>( (` + uY + `*` + vZ + `) - (` + uZ + `*` + vY + `) )</td>
		<td>,</td>
		<td>( (` + uZ + `*` + vX + `) - (` + uX + `*` + vZ + `) )</td>
		<td>,</td>
		<td>( (` + uX + `*` + vY + `) - (` + uY + `*` + vX + `) )</td>
		<td>=</td>
		<td>`+ `u X v` +`</td>

	</tr>
	
	<tr>
		<td>( (` + x1 + `) - (` + x2 + `) )</td>
		<td>,</td>
		<td>( (` + y1 + `) - (` + y2 + `) )</td>
		<td>,</td>
		<td>( (` + z1 + `) - (` + z2 + `) )</td>
		<td>=</td>
		<td>`+ `u X v` +`</td>

	</tr>	
	
	<tr>
		<td>` + X + `</td>
		<td>,</td>
		<td>` + Y + `</td>
		<td>,</td>
		<td>` + Z + `</td>
		<td>=</td>
		<td>`+ `u X v` +`</td>
	</tr>

	</table>`)
	
	
}

