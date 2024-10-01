# Create your models here.
from django.db import models


class Ville(models.Model):
    nom_ville = models.CharField(max_length=100)
    code_postal = models.IntegerField()
    prix_m2 = models.IntegerField()
    
    def __str__(self):
        return f"{self.code_postal} {self.nom_ville}"


class Local(models.Model):
    nom_local = models.CharField(max_length=100)
    ville = models.ForeignKey(Ville, on_delete=models.PROTECT)
    surface_local = models.IntegerField()
    
    def __str__(self):
        return f"{self.nom_local} {self.ville} {self.surface_local}m2"
        
    def costs(self):
    	return (self.surface_local) * (self.ville.prix_m2)

class Machine(models.Model):
    nom_machine = models.CharField(max_length=100)
    prix_machine = models.IntegerField()
    n_serie_machine = models.IntegerField()
    
    def __str__(self):
        return f"{self.nom_machine}{self.n_serie_machine}"
        
    def costs(self):
    	return  self.prix_machine

class Objet(models.Model):
    nom_objet = models.CharField(max_length=100)
    prix_objet = models.IntegerField()
    def __str__(self):
        return f"{self.nom_objet}"
      
    def costs(self):
    	return self.prix_objet 
       

class Usine(Local):
    machines = models.ManyToManyField(Machine)

    def costs(self):
        prix_machines = 0
        for machine in self.machines.all():
            prix_machines = prix_machines + machine.prix_machine
        return prix_machines
    	

class SiegeSocial(Local):
    pass


class Ressource(Objet):
    pass


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(Ressource, on_delete=models.PROTECT)
    quantite = models.IntegerField()
    
    def costs(self):     
        return self.ressource.prix_objet * self.quantite

    


class Stock(models.Model):
    objet = models.ForeignKey(Objet, on_delete=models.PROTECT)
    nombre = models.IntegerField()
    usine = models.ForeignKey(Usine, on_delete=models.PROTECT)
    
    def __str__(self):
        return f"{self.objet}"
        
    

class Etape(models.Model):
    nom_etape = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntegerField()
    etape_suivante = models.ForeignKey("self",blank= True, null = True ,on_delete=models.PROTECT)
    def __str__(self):
        return f"{self.nom_etape}"

class Produit(models.Model):
    premiere_etape = models.ForeignKey(Etape, on_delete=models.PROTECT)
