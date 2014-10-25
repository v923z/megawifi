import web
import sys
import telnetlib
import simplejson

urls = ('/',  'Index')
render = web.template.render('templates/')
app = web.application(urls, globals())

tn = telnetlib.socket.create_connection(('10.10.100.254', 8899))

class Index(object):
	def GET(self):
		return render.gui()
			
	def POST(self):
		data = simplejson.loads(web.data())
		print data
		tn.send(data['data'])
		return False

if __name__ == "__main__": 
	app.run()
