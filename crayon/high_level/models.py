# Create your models here.
from django.db import models


class Ville(models.Model):
    nom_ville = models.CharField(max_length=100)
    code_postal = models.IntergerField()
    prix_m2 = models.IntergersField()


class Local(models.Model):
    nom_local = models.CharField(max_length=100)
    ville = models.ForeignKey(Ville, on_delete=models.PROTECT)
    surface_local = models.IntergerField()


class Machine(models.Model):
    nom_machine = models.CharField(max_length=100)
    prix_machine = models.IntergersField()
    n_serie_machine = models.IntergersField()


class Objet(models.Model):
    nom_objet = models.CharField(max_length=100)
    prix_objet = models.IntergersField()


class Usine(Local):
    machines = models.ManyToManyField(Machine)


class SiegeSocial(Local):
    pass


class Ressource(Objet):
    pass


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(Ressource, on_delete=models.PROTECT)
    quantite = models.IntergersField()


class Stock(models.Model):
    objet = models.ForeignKey(Objet, on_delete=models.PROTECT)
    nombre = models.IntergersField()


class Etape(models.Model):
    nom_etape = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntergersField()
    etape_suivante = models.ForeignKey("self", on_delete=models.PROTECT)


class Produit(models.Model):
    premiere_etape = models.ForeignKey(Etape, on_delete=models.PROTECT)
