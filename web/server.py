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
	
	def pass_message(self, data):
		response = None
		return 123
		if self.channel:
			self.channel.write(data.get('command'))
			if data.get('format') in ('ascii'):
				response = self.channel.read_until(';', self.timeout)
			elif data.get('format') in ('binary'):
				data.get('byte_length')
				pass
				#response = self.channel.read_until(, self.timeout)
		return response
		
	def close(self):
		if self.channel: self.channel.close()

channel = Channel('10.10.100.254', 8899)
#print channel

class Index(object):
	def GET(self):
		link = web.input()
		#if link.name.endswith('.html'): 
		print link.name
		with open(link.name, 'r') as fin:
			html = fin.read()
		return html
			
	def POST(self):
		data = simplejson.loads(web.data())
		print data
		if data.get('type') in ('command'):
			return simplejson.dumps({'response': channel.pass_message(data)})
		else:
			return simplejson.dumps({'response': 'not a command'})
		
if __name__ == "__main__": 
	app.run()
