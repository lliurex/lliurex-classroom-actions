import copy
import time
import os
import multiprocessing

class NecosLiteServer:
	

	def __init__(self):
		
		self.epoptes_cli="/usr/share/lliurex-classroom-actions/epoptes/epoptes-cli"
		
	#def init

	
	def startup(self,options):
		
		self.internal_variable=copy.deepcopy(objects["VariablesManager"].get_variable("NECOSLITE"))
		
		if self.internal_variable==None:
			try:

				self.internal_variable=self.initialize_variable()
				objects["VariablesManager"].add_variable("NECOSLITE",copy.deepcopy(self.internal_variable),"","NECOS LITE variable","lliurex-classroom-actions-data",True)
				
			except Exception as e:
				print e
	
	#def startup

	
	def initialize_variable(self):
		
		var={}
		var["execute"]=None
		var["args"]=None
		var["last_execution"]=0
		
		return var
		
	#def initialize_variable
	
	


	def check_variable(self,variable):

		try:
			if not type(variable)==dict:
				return False
			if not type(variable["execute"])==str:
				return False
			if not (type(variable["args"])==dict or variable["args"]==None):
				return False
			if not type(variable["last_execution"])==float:
				return False
		except:
			return False

		return True

	#def check_variable

	
	def manual_client_list_check(self):
		
		objects["VariablesManager"].manual_client_list_check()
		return True
		
	#def manual_client_list_check


	def execute_function(self,call,args):
		
		new_var=self.initialize_variable()
		new_var["execute"]=call
		new_var["args"]=args
		new_var["last_execution"]=time.time()
		
		if self.check_variable(new_var):
			self.save_variable(new_var)
	
		return {"status":True,"msg":""}
	
	
	def save_variable(self,variable=None):

		if variable==None:
			variable=copy.deepcopy(self.internal_variable)
		else:
			if not self.check_variable(variable):
				return {"status":False,"msg":"Variable does not have the expected structure"}
			self.internal_variable=copy.deepcopy(variable)
		
		objects["VariablesManager"].set_variable("NECOSLITE",variable)
		
		return {"status":True,"msg":""}
		
	#def save_variable
	
	
	def execute_epoptes_action(self,ip,action):
		
		if type(ip) != str:
			ip=""

		objects["EpoptesServer"].register_ip("127.0.0.1")
		command="IP_FILTER=%s %s %s"%(ip,self.epoptes_cli,action)
		p=multiprocessing.Process(target=os.system,args=(command,))
		p.daemon=True
		p.start()
		
		return {"status":True,"msg":""}
		
	#def lock_screens
	
	def unlock_screens(self):
		
		objects["EpoptesServer"].register_ip("127.0.0.1")
		command="%s unlock_screen"%self.epoptes_cli
		p=multiprocessing.Process(target=os.system,args=(command,))
		p.daemon=True
		p.start()
		
		return {"status":True,"msg":""}
		
	#def lock_screens
	