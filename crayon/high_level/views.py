# Create your views here.

from django.http import JsonResponse
from .models import Ville
from .models import Local
from .models import Machine
from .models import Objet
from .models import Usine
from .models import QuantiteRessource
from .models import Stock
from .models import Etape
from .models import Produit


from django.views.generic import DetailView

class VilleJsonDetailView(DetailView) : 
	model = Ville
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json()) 
		
class LocalJsonDetailView(DetailView) : 
	model = Local
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class MachineJsonDetailView(DetailView) : 
	model = Machine
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())

class ObjetJsonDetailView(DetailView) : 
	model = Objet
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class UsineJsonDetailView(DetailView) : 
	model = Usine
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class QuantiteRessourceJsonDetailView(DetailView) : 
	model = QuantiteRessource
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class StockJsonDetailView(DetailView) : 
	model = Stock
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class EtapeJsonDetailView(DetailView) : 
	model = Etape
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
class ProduitJsonDetailView(DetailView) : 
	model = Produit
	
	def render_to_response (self,context, **response_kwargs):
		return JsonResponse(self.object.json())
		
