CREATE TABLE [dbo].[Homework]
(
	[ID]	INT IDENTITY (1,1)	NOT NULL,
	[HomeworkTitle] NVARCHAR(100)	NOT NULL,
	[Importance]	NVARCHAR(10) NOT NULL,
	[DueDate] NVARCHAR(12) NOT NULL,
	[DueTime] NVARCHAR(12) NOT NULL,
	[Department] NVARCHAR(5) NOT NULL,
	[CourseNumber] INT NOT NULL,
	[Notes] NVARCHAR(500)

	CONSTRAINT [PK_dbo.Homework] PRIMARY KEY CLUSTERED ([ID] ASC)

)

INSERT INTO [dbo].[Homework] (HomeworkTitle, Importance, DueDate, DueTime, Department, CourseNumber, Notes) VALUES
			('Research Paper', 'High', '10/21/2103','05:30:00 AM','WR','302','Need to find sources'),
			('Math Chapter 5', 'Low', '10/21/2012','10:20:08 AM','MTH','105','Must read book'),
			('Presentation', 'Average', '10/21/2012','10:20:08 PM','COM','215','FInish up powerpoint'),
			('Calculator', 'Average', '09/21/2012','04:00:00 PM','CS','415','Look up documentation'),
			('Lab 4', 'Low', '6/04/1993','12:30:00 PM','BIO','123','Finsih report')

GO