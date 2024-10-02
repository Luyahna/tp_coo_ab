"""
URL configuration for crayon project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""

from django.contrib import admin
from django.urls import path
from high_level.views import VilleJsonDetailView
from high_level.views import LocalJsonDetailView
from high_level.views import MachineJsonDetailView
from high_level.views import ObjetJsonDetailView
from high_level.views import UsineJsonDetailView
from high_level.views import QuantiteRessourceJsonDetailView
from high_level.views import StockJsonDetailView
from high_level.views import EtapeJsonDetailView
from high_level.views import ProduitJsonDetailView

urlpatterns = [
    path("admin/", admin.site.urls),

    path('villes/<int:pk>/', VilleJsonDetailView.as_view(), name='ville-detail'),
    path('local/<int:pk>/', LocalJsonDetailView.as_view(), name='local-detail'),
    path('machine/<int:pk>/', MachineJsonDetailView.as_view(), name='machine-detail'),
    path('objet/<int:pk>/', ObjetJsonDetailView.as_view(), name='objet-detail'),
    path('usine/<int:pk>/', UsineJsonDetailView.as_view(), name='usine-detail'),
    path('quantiteressource/<int:pk>/', QuantiteRessourceJsonDetailView.as_view(), name='quantiteressource-detail'),
    path('stock/<int:pk>/', StockJsonDetailView.as_view(), name='stock-detail'),
    path('etape/<int:pk>/', EtapeJsonDetailView.as_view(), name='etape-detail'),
    path('produit/<int:pk>/', ProduitJsonDetailView.as_view(), name='produit-detail')]
