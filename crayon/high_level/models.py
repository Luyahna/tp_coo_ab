# Create your models here.
import json
from django.db import models
from django.views.generic import DetailView

class Ville(models.Model):
    nom_ville = models.CharField(max_length=100)
    code_postal = models.IntegerField()
    prix_m2 = models.IntegerField()
    
    def __str__(self):
        return f"{self.code_postal} {self.nom_ville}"
    
    def json(self):
        return {
            'nom_ville': self.nom_ville,
            'code_postal': self.code_postal,
            'prix_m2': self.prix_m2
        }


class Local(models.Model):
    nom_local = models.CharField(max_length=100)
    ville = models.ForeignKey(Ville, on_delete=models.PROTECT)
    surface_local = models.IntegerField()
    
    def __str__(self):
        return f"{self.nom_local} {self.ville} {self.surface_local}m2"
        
    def costs(self):
    	return (self.surface_local) * (self.ville.prix_m2)
    
    def json(self):
        return {
            'nom_local': self.nom_local,
            'ville': self.ville.id,
            'surface_local': self.surface_local
        }   	
    

class Machine(models.Model):
    nom_machine = models.CharField(max_length=100)
    prix_machine = models.IntegerField()
    n_serie_machine = models.IntegerField()
    
    def __str__(self):
        return f"{self.nom_machine}{self.n_serie_machine}"
        
    def costs(self):
    	return  self.prix_machine
    
    def json(self):
        return {
            'nom_machine': self.nom_machine,
            'prix_machine': self.prix_machine,
            'n_serie_machine': self.n_serie_machine
        }  
        
class Objet(models.Model):
    nom_objet = models.CharField(max_length=100)
    prix_objet = models.IntegerField()
    
    def __str__(self):
        return f"{self.nom_objet}"
      
    def costs(self):
    	return self.prix_objet 
    
    def json(self):
        return {
            'nom_objet': self.nom_objet,
            'prix_objet': self.prix_objet
        } 
       

class Usine(Local):
    machines = models.ManyToManyField(Machine)

    def costs(self):
        prix_machines = 0
        for machine in self.machines.all():
            prix_machines = prix_machines + machine.prix_machine
        return prix_machines
                  
    def json(self):
        liste_machines = []
        for machine in self.machines.all():
            liste_machines.append(machine.id)     
        return {
            'machines': liste_machines
        } 


class SiegeSocial(Local):
    pass


class Ressource(Objet):
    pass


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(Ressource, on_delete=models.PROTECT)
    quantite = models.IntegerField()
    
    def costs(self):     
        return self.ressource.prix_objet * self.quantite
        
    def json(self):
        return {
            'ressource': self.ressource.id,
            'quantite': self.quantite
        } 
    


class Stock(models.Model):
    objet = models.ForeignKey(Objet, on_delete=models.PROTECT)
    nombre = models.IntegerField()
    usine = models.ForeignKey(Usine, on_delete=models.PROTECT)
    
    def __str__(self):
        return f"{self.objet}"
        
    def json(self):
        return {
            'objet': self.objet.id,
            'nombre': self.nombre,
            'usine': self.usine.id
        }      
        
    

class Etape(models.Model):
    nom_etape = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntegerField()
    etape_suivante = models.ForeignKey("self",blank= True, null = True ,on_delete=models.PROTECT)
    
    def __str__(self):
        return f"{self.nom_etape}"
        
    def json(self):
        return {
            'nom_etape': self.nom_etape,
            'machine': self.machine.id,
            'quantite_ressource': self.quantite_ressource.id,
            'duree': self.duree,
            'etape_suivante': self.etape_suivante.id
        }         


class Produit(models.Model):
    premiere_etape = models.ForeignKey(Etape, on_delete=models.PROTECT)
         
    def json(self):
        return {
            'premiere_etape': self.premiere_etape.id
        }      
