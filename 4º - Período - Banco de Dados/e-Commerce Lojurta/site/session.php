<?php
	session_start();
	if($lojista) {
		$login = $_POST['CNPJ'];
		$senha = $_POST['pasSt'];
	} else {
		$login = $_POST['user'];
		$senha = $_POST['pasCli'];
	}


	include 'dbConnection.php';
	
	
		$_SESSION['login'] = $login;
		$_SESSION['senha'] = $senha;
		if($lojista)
			$_SESSION['tipo'] = 'loja';
		else
			$_SESSION['tipo'] = 'cliente';
	
		header('location:index.php');
?>