 <?php 
  // Verifica se houve POST e se o usuário ou a senha é(são) vazio(s)
  include 'dbConnection.php';
  
    if (isset($_POST['CNPJ']) and isset($_POST['senha'])) {
              
		$CNPJ = $_POST['CNPJ'];
		$pasSt = $_POST['senha'];
	   
		$query = mysqli_query($link,"SELECT * 
										FROM loja
										WHERE CNPJ='".$CNPJ."'
											AND senha='".$pasSt."'
															");
		$lojista = true;
		
	}
	else if (isset($_POST['user']) and isset($_POST['password'])) {
		$user = $_POST['user'];
		$pasCli = $_POST['password'];
		//header("Location: index.php"); exit;
    
		  
		// Validação do usuário/senha digitados
	   
		$query = mysqli_query($link,"SELECT * 
										FROM cliente
										WHERE login='".$user."'
											AND senha='".$pasCli."'
															");
		$lojista = false;
		
	}

	$rows = mysqli_num_rows($query);
    if (!$rows) {
        // Mensagem de erro quando os dados são inválidos e/ou o usuário não foi encontrado	
		$valide = false;
		require_once("index.php");
		exit;
    } else {
        // Salva os dados encontados na variável $resultado
        $resultado = mysqli_fetch_assoc($query);
		require_once("session.php");
    }
?>	