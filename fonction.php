<?php
include 'C:/xampp/htdocs/allo/connexion.php';
include 'C:/xampp/htdocs/allo/classse.php';
function ajouteroffre($offre){
			$sql="INSERT INTO offre (idoffre) 
			VALUES (:idoffre)";
			$db = config::getConnexion();
			try{
				$query = $db->prepare($sql);
				$query->execute([
					'idoffre' => $offre->getidoffre(),
					
				]);			
			}
			catch (Exception $e){
				echo 'Erreur: '.$e->getMessage();
			}			
		}


        ?>