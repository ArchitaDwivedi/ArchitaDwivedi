from flask import *
from flask_restful import Resource,Api

app=Flask(__name__)
api=Api(app)

class Start(Resource):
	def get(self, ip):
		from selenium import webdriver
		from selenium.webdriver.common.keys import Keys
		from selenium.webdriver.chrome.options import Options
		import time
		import subprocess


		iplist = []						
		unreachableips=[]
		reachableips=[]

		def pingtest(ipn):
			print ("""			
					Testing connectivity to IPs...Please wait...		
					""")

			output = subprocess.Popen(['ping','-c','1','-t','2000', ipn], stdout=subprocess.PIPE).communicate()[0]
			    
			if "Destination host unreachable" in output.decode('utf-8'):
			    print (n, "is Offline")
			    unreachableips.append(ipn)
			elif "Request timed out" in output.decode('utf-8'):
			    print (n, "is Offline")
			    unreachableips.append(ipn)
			else:
			    print(ipn,"is reachable")
			    reachableips.append(ipn)

		pingtest(ip)

		unreachableips=[]
		reachableips=[]

		
		options = Options()
		options.add_argument('--headless')
		options.add_argument('--disable-gpu')
		bot = webdriver.Chrome(executable_path="/Users/architadwivedi/Desktop/t/chromedriver",chrome_options=options)

		bot.set_page_load_timeout(30)

		def start(ipn):
			URL = "http://%s/laboratories.php"%ipn
			x = bot.get(URL)
			bot.maximize_window()
			bot.implicitly_wait(20)
			bot.find_element_by_xpath('//*[@id="lab2"]/a[2]/img').click()	#4-RouterLab
			time.sleep(1)
			bot.find_element_by_xpath('/html/body/form/div[2]/div/div[2]/p/select/option[2]').click()	#Basic-IPv6
			time.sleep(1)
			bot.find_element_by_xpath('/html/body/form/div[2]/div/div[2]/input[1]').click()
			time.sleep(1)
			bot.find_element_by_xpath('//*[@id="lab2"]/a[1]').click()
			time.sleep(1)
			bot.find_element_by_xpath('//*[@id="tabs"]/ul/li[1]/a[1]').click()
			time.sleep(1)
			bot.find_element_by_xpath('//*[@id="dev_start_all"]').click()
			time.sleep(1)
			return 200

		
		status = start(ip)
		if status==200:
			print (ip,': Device started.')
			return {'status': 200}
		else:
			print("There was some error in starting the device.")
			return {'error':500}

		bot.quit()
		return

api.add_resource(Start,"/hello/<string:ip>")
#api.add_resource(Secondary,'/foo')

if __name__ == '__main__':
	app.run(debug=True)