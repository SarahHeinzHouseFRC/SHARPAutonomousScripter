import pysftp

with pysftp.Connection('roborio-3260.local', username = 'lvuser', password = " ") as sftp:
	sftp.put("/home/lucas/Desktop/autonomousVariables.csv")
	sftp.close()


