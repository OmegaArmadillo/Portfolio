
CREATE TABLE [dbo].[Teams]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Name]	NVARCHAR(50)	NOT NULL,
	[CoachID] INT	NOT NULL,

	CONSTRAINT [PK_dbo.Teams] PRIMARY KEY CLUSTERED ([ID] ASC)
);

CREATE TABLE [dbo].[Events]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Name]	NVARCHAR(20)	NOT NULL,

	CONSTRAINT [PK_dbo.Events] PRIMARY KEY CLUSTERED ([ID] ASC)
);

CREATE TABLE [dbo].[Meets]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Location]	NVARCHAR(50)	NOT NULL,
	[Date] DATETIME	NOT NULL,

	CONSTRAINT [PK_dbo.Meets] PRIMARY KEY CLUSTERED ([ID] ASC)
);

CREATE TABLE [dbo].[Coaches]
(	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Name]	NVARCHAR(50)	NOT NULL,

	CONSTRAINT [PK_dbo.Coaches] PRIMARY KEY CLUSTERED ([ID] ASC)
);


CREATE TABLE [dbo].[Athletes]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Name]	NVARCHAR(50)	NOT NULL,
	[TeamID] INT	NOT NULL,
	[Gender] NVARCHAR(20)	NOT NULL,

	CONSTRAINT [PK_dbo.Athletes] PRIMARY KEY CLUSTERED ([ID] ASC),
	CONSTRAINT [FK_dbo.Athletes_dbo.Teams_ID] FOREIGN KEY ([TeamID]) REFERENCES [dbo].[Teams] ([ID])
);

/*
CREATE TABLE [dbo].[Results]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[Location] NVARCHAR(50)	NOT NULL,
	[Date] DATETIME	NOT NULL,
	[Team] NVARCHAR(50)	NOT NULL,
	[Coach] NVARCHAR(50)	NOT NULL,
	[Event] NVARCHAR(20)	NOT NULL,
	[Gender] NVARCHAR(20)	NOT NULL,
	[Athlete] NVARCHAR(50)	NOT NULL,
	[RaceTime] REAL NOT NULL

	CONSTRAINT [PK_dbo.RaceTimes] PRIMARY KEY CLUSTERED ([ID] ASC),
	CONSTRAINT [FK_dbo.Results_dbo.Meets_Locaiton] FOREIGN KEY ([Location]) REFERENCES [dbo].[Meets] ([Location]),
	CONSTRAINT [FK_dbo.Results_dbo.Event_Name] FOREIGN KEY ([Event]) REFERENCES [dbo].[Events] ([Name]),
	CONSTRAINT [FK_dbo.Results_dbo.Athlete_Name] FOREIGN KEY ([Athlete]) REFERENCES [dbo].[Athletes] ([Name])
);

*/


CREATE TABLE [dbo].[Results]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[MeetID] INT	NOT NULL,
	[EventID] INT	NOT NULL,
	[AthleteID]INT	NOT NULL,
	[RaceTime] REAL NOT NULL

	CONSTRAINT [PK_dbo.RaceTimes] PRIMARY KEY CLUSTERED ([ID] ASC),
	CONSTRAINT [FK_dbo.Results_dbo.Meets_ID] FOREIGN KEY ([MeetID]) REFERENCES [dbo].[Meets] ([ID]),
	CONSTRAINT [FK_dbo.Results_dbo.Event_ID] FOREIGN KEY ([EventID]) REFERENCES [dbo].[Events] ([ID]),
	CONSTRAINT [FK_dbo.Results_dbo.Athlete_ID] FOREIGN KEY ([AthleteID]) REFERENCES [dbo].[Athletes] ([ID])
);

GO