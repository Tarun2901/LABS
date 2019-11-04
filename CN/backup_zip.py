import os,zipfile,sys

def getBackup(folder):
	#folder = os.path.abspath(folder)
	number = 1
	while True:
		zipfilename = os.path.basename(folder) + '_' + str(number) + '.zip'
		if not os.path.exists(zipfilename):
			break
		number += 1	
		
	zipfilename = os.path.join(os.path.dirname(folder),zipfilename)
	print(zipfilename)	
	#Creating the zipfile
	print('Creating %s ...'%(zipfilename))
	backupZip = zipfile.ZipFile(zipfilename,'w')
	#Write to the zipfile
	for foldername,subfolders,files in os.walk(folder):
		backupZip.write(foldername)

		for filename in files:
			if filename.endswith('.zip'):
				continue
			backupZip.write(os.path.join(foldername,filename))
	
	backupZip.close()
	print('Done...')

getBackup(sys.argv[1])	