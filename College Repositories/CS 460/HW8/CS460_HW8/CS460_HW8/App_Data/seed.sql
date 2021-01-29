
-- ################### SEED DATA ######################

-- Extract data from .csv file and load into our db

-- Create a staging table to hold all the seed data.  We'll query this 
-- table in order to extract what we need to then insert into our real
-- tables.
CREATE TABLE [dbo].[AllData]
(
	[Location] NVARCHAR(50),
	[MeetDate] DATETIME,
	[Team] NVARCHAR(50),
	[Coach] NVARCHAR(50),
	[Event] NVARCHAR(20),
	[Gender] NVARCHAR(20),
	[Athlete] NVARCHAR(50),
	[RaceTime] REAL
);

-- Hard code the full path to the csv file.  It'll be better this way 
-- when we run this in HW 9 to build an Azure db 
BULK INSERT [dbo].[AllData]
	FROM 'C:\Users\matth\Documents\racetimes.csv'
	WITH
	(
		FIELDTERMINATOR = ',',
		ROWTERMINATOR = '\n',
		FIRSTROW = 2
	);

-- Load coaches data, no foreign keys here to worry about so we can 
-- do a straight insert of just the distinct values
INSERT INTO [dbo].[Coaches] (Name)
	SELECT DISTINCT Coach from [dbo].[AllData];

-- Load Team data, a team has a coach so we need to find the correct entry in the 
-- Coaches table so we can set the foreign key appropriately
INSERT INTO [dbo].[Teams] (Name,CoachID)
	SELECT DISTINCT ad.Team,cs.ID
		FROM dbo.AllData as ad, dbo.Coaches as cs
		WHERE ad.Coach = cs.Name;

-- Load all the other tables in a similar fashion.  Race results is the hardest since
-- it has several FK's.  Think joins.



--                    Athletes                      

-- Load coaches data, no foreign keys here to worry about so we can 
-- do a straight insert of just the distinct values
INSERT INTO [dbo].[Athletes] (Name, TeamID, Gender)
	SELECT DISTINCT ad.Athlete, tm.ID, ad.Gender 
	FROM dbo.AllData as ad, dbo.Teams as tm
	WHERE ad.Team = tm.Name;


--                    Events                      

-- Load coaches data, no foreign keys here to worry about so we can 
-- do a straight insert of just the distinct values
INSERT INTO [dbo].[Events] (Name)
	SELECT DISTINCT Event
	from [dbo].[AllData];


--                    Location                      

-- Load coaches data, no foreign keys here to worry about so we can 
-- do a straight insert of just the distinct values
INSERT INTO [dbo].[Meets] (Location, Date)
	SELECT DISTINCT Location, MeetDate
	from [dbo].[AllData];



--                   Results                     
/*
-- Load coaches data, no foreign keys here to worry about so we can 
-- do a straight insert of just the distinct values
INSERT INTO [dbo].[Results] (Location, Date, Team, Coach, Event, Gender, Athlete, RaceTime)
	SELECT mt.Location, mt.Date, tm.Name, cs.Name, es.Name, ats.Gender, ats.Name, ad.RaceTime
	from dbo.AllData as ad, dbo.Meets as mt, dbo.Teams as tm, dbo.Coaches as cs, dbo.Events as es, dbo.Athletes as ats
	Where ad.Location = mt.Location 
	AND ad.MeetDate = mt.Date
	AND ad.Team = tm.Name
	AND ad.Coach = cs.Name
	AND ad.Event = es.Name
	AND ad.Gender = ats.Gender
	AND ad.Athlete = ats.Name
	;
	*/

	INSERT INTO [dbo].[Results] (MeetID, EventID, AthleteID, RaceTime)
	SELECT mt.ID, es.ID, ats.ID, ad.RaceTime
	from dbo.AllData as ad, dbo.Meets as mt, dbo.Events as es, dbo.Athletes as ats
	Where ad.Location = mt.Location 
	AND ad.Event = es.Name
	AND ad.Athlete = ats.Name;


-- We don't need this staging table anymore so clear it away
DROP TABLE [dbo].[AllData];


