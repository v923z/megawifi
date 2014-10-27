import web
import sys
import telnetlib
import simplejson

urls = ('/',  'Index')
render = web.template.render('templates/')
app = web.application(urls, globals())

class Channel(object):
	def __init__(self, address, port):
		self.channel = None
		self.timeout = 5
		#try:
			#self.channel = telnetlib.Telnet(address, port)
		#except:
			#print "Couldn't open port for communication"
	
	def pass_message(self, message):
		response = None
		if self.channel:
			self.channel.write(message.get('command'))
			if message.get('format') in ('ascii'):
				response = self.channel.read_until(';', self.timeout)
			elif message.get('format') in ('binary'):
				pass
				#response = self.channel.read_until(, self.timeout)
		return response
		
	def close(self):
		self.channel.close()

channel = Channel('10.10.100.254', 8899)
#print channel

class Index(object):
	def GET(self):
		link = web.input()
		return render.oscilloscope()
			
	def POST(self):
		data = simplejson.loads(web.data())
		if data.get('type') in ('command'):
			return simplejson.dumps({'response': channel.pass_message(data)})
		else:
			return simplejson.dumps({'response': 'not a command'})
		
if __name__ == "__main__": 
	app.run()
