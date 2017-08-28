<!doctype html> 

<?php
if (!isset($_SESSION)) session_start();
if(!(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja'))
	header('location:index.php');
$logado = $_SESSION['login'];
?>

	<?php
		if(isset($newPromo)){
			if($newPromo){
				echo"<script type='text/javascript'>";
				echo "alert('Promocao cadastrado com sucesso!');";
				echo "</script>";
			}
			else{
				echo"<script type='text/javascript'>";
				echo "alert('Não foi possível cadastrar a promocao!');";
				echo "</script>";
			}
		}
		
		if(isset($deletePromo)){
			if($deletePromo){
				echo"<script type='text/javascript'>";
				echo "alert('Promocao deleteada com sucesso!');";
				echo "</script>";
			}
			else{
				echo"<script type='text/javascript'>";
				echo "alert('Não foi possível deletar a promocao!');";
				echo "</script>";
			}
		}
	?>

<html class="no-js">

	<head>
		<meta charset="utf-8"/>
		<title>FOLDER TEMPLATE</title>
		
		<!--[if lt IE 9]>
			<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
		<![endif]-->
		<link rel="stylesheet" media="all" href="css/style.css"/>
		<meta name="viewport" content="width=device-width, initial-scale=1"/>
		<!-- Adding "maximum-scale=1" fixes the Mobile Safari auto-zoom bug: http://filamentgroup.com/examples/iosScaleBug/ -->		
				
		<!-- JS -->
		<script src="js/jquery-1.7.1.min.js"></script>
		<script src="js/custom.js"></script>
		<script src="js/tabs.js"></script>
		<script src="js/css3-mediaqueries.js"></script>
		<script src="js/jquery.columnizer.min.js"></script>
		
		<!-- Isotope -->
		<script src="js/jquery.isotope.min.js"></script>
		
		<!-- Lof slider -->
		<script src="js/jquery.easing.js"></script>
		<script src="js/lof-slider.js"></script>
		<link rel="stylesheet" href="css/lof-slider.css" media="all"  /> 
		<!-- ENDS slider -->
		
		<!-- Tweet -->
		<link rel="stylesheet" href="css/jquery.tweet.css" media="all"  /> 
		<script src="js/tweet/jquery.tweet.js" ></script> 
		<!-- ENDS Tweet -->
		
		<!-- superfish -->
		<link rel="stylesheet" media="screen" href="css/superfish.css" /> 
		<script  src="js/superfish-1.4.8/js/hoverIntent.js"></script>
		<script  src="js/superfish-1.4.8/js/superfish.js"></script>
		<script  src="js/superfish-1.4.8/js/supersubs.js"></script>
		<!-- ENDS superfish -->
		
		<!-- prettyPhoto -->
		<script  src="js/prettyPhoto/js/jquery.prettyPhoto.js"></script>
		<link rel="stylesheet" href="js/prettyPhoto/css/prettyPhoto.css"  media="screen" />
		<!-- ENDS prettyPhoto -->
		
		<!-- poshytip -->
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-twitter/tip-twitter.css"  />
		<link rel="stylesheet" href="js/poshytip-1.1/src/tip-yellowsimple/tip-yellowsimple.css"  />
		<script  src="js/poshytip-1.1/src/jquery.poshytip.min.js"></script>
		<!-- ENDS poshytip -->
		
		<!-- JCarousel -->
		<script type="text/javascript" src="js/jquery.jcarousel.min.js"></script>
		<link rel="stylesheet" media="screen" href="css/carousel.css" /> 
		<!-- ENDS JCarousel -->
		
		<!-- GOOGLE FONTS -->
		<link href='http://fonts.googleapis.com/css?family=Voltaire' rel='stylesheet' type='text/css'>

		<!-- modernizr -->
		<script src="js/modernizr.js"></script>
		
		<!-- SKIN -->
		<link rel="stylesheet" media="all" href="css/skin.css"/>
		
		<!-- Less framework -->
		<link rel="stylesheet" media="all" href="css/lessframework.css"/>
		
		<!-- jplayer -->
		<link href="player-skin/jplayer-black-and-yellow.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" src="js/jquery.jplayer.min.js"></script>
		
		<!-- flexslider -->
		<link rel="stylesheet" href="css/flexslider.css" >
		<script src="js/jquery.flexslider.js"></script>
		
		<!-- reply move form -->
		<script src="js/moveform.js"></script>
		
		<!-- star -->
		<link rel="stylesheet" media="all" href="css/star.css"/>
		
	</head>
	
	
	<body class="page" onload="">
	
		<!-- HEADER -->
		<header>
			<div class="wrapper cf">
				
				<div id="logo">
					<a href="index.php"><img  src="img/logo.png" alt="Simpler"></a>
				</div>
				
				<!-- nav -->
	<ul id="nav" class="sf-menu">
	<li ><a href="index.php">HOME</a></li>
<?php

if(!(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja')) {
	echo '<li><a href="products.php">PRODUTOS</a></li>';
	echo '<li><a href="#">LOJAS</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'cliente') {
	echo '<li><a href="history.php">HISTÓRICO</a></li>';
	echo '<li><a href="car.php">CARRINHO</a></li>';
}

if(isset($_SESSION['tipo']) && $_SESSION['tipo'] == 'loja') {
	echo '<li><a href="#">HISTORICO</a></li>';
	echo '<li><a href="registerProducts.php">CADASTRAR PRODUTO</a></li>';
	echo '<li class="current-menu-item"><a href="gerenPromo.php">GERENCIAR PROMOÇÃO</a></li>';
}
?>

					
					<li><a href="contact.php">CONTATO</a></li>
<?php
	if(!(isset($_SESSION['tipo']))) {
				echo<<< HTML
					<li><a href="#">LOGIN</a>
						<ul>
							<li>
								<script type="text/javascript" src="js/form-validation.js"></script>
								<table>
									<tr>
										<td>
											<form action="validate.php" method="POST">
											<fieldset style="width:100px" size="100">
												Usuário 							
												<input name="user"  id="user" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="password"  id="password" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerCliente.php">Cadastrar cliente </a>
											</fieldset>
											</form>
											</script>
										</td>
										<td>								
											<script type="text/javascript" src="js/form-validation.js"></script>
											<form action="validate.php" method="POST">
											<fieldset>
												CNPJ 							
												<input name="CNPJ"  id="CNPJ" type="text" class="form-poshytip" size="7"/>
												<p>
												Senha <input name="senha"  id="senha" type="password" class="form-poshytip" size="7"/>
											<input name="enviar"  id="enviar" type="submit" class="form-poshytip" />
											<a href="registerLoja.php">Cadastrar loja </a>
											</fieldset>
											</form>
											</script>
										</td>
									</tr>
								</table>
							</li>
						</ul>
						
					</li>
HTML;
	} else {
		echo '<li><a href="logout.php">SAIR</a></li>';
	}
?>
				</ul>
				<div id="combo-holder"></div>
				<!-- ends nav -->

			</div>
		</header>
		<!-- ENDS HEADER -->
		
		<!-- MAIN -->
		<div id="main">
			<div class="wrapper cf">
			
			
				
			<!-- page content-->
        	<div id="page-content" class="cf">        	
	        		
	        	
	 
				<!-- page content-->
				
				<p><h3>CADASTRAR PROMOÇÕES</h3></p>
				<!-- form -->
				<script type="text/javascript" src="js/form-validation.js"></script>
				<form id="contactForm" action="insertPromo.php" method="post">
					<fieldset>
					
					<p>
							<label for="nombre" >Nome</label>
							<input name="nombre"  id="nombre" type="text" class="form-poshytip" />
					</p>
														
<label for="produto">Produto</label>
<select id="produto" name="produto">
<?php
	include 'dbConnection.php';
	
	$query = mysqli_query($link,"SELECT *
									FROM produto
									WHERE Loja_idLoja IN (SELECT idLoja
															FROM loja
															WHERE CNPJ = '".$logado."')");
	
	while ($aux = mysqli_fetch_array($query))
		echo '<option value="'.$aux['idProduto'].'"> '.$aux['nome'];
	
?>						
</select>
						
						<p>
							<label for="desconto" >Desconto</label>
							<input name="desconto"  id="desconto" type="text" class="form-poshytip" />
						</p>
						
						<p>
							<label for="dateIni">Data para inicio da promoção</label>
							<input name="dateIni"  id="dateIni" type="date" class="form-poshytip"/>
						</p>
						
						<p>
							<label for="horaIni">Hora para inicio da promoção</label>
							<input name="horaIni"  id="horaIni" type="time" class="form-poshytip"/>
						</p>
						
						<p>
							<label for="dateFim">Data para inicio da promoção</label>
							<input name="dateFim"  id="dateFim" type="date" class="form-poshytip"/>
						</p>
						
						<p>
							<label for="horaFim">Hora para fim da promoção</label>
							<input name="horaFim"  id="horaFim" type="time" class="form-poshytip"/>
						</p>
					
						<p><input type="submit" value="Enviar" name="submit" id="submit" /> <span id="error" class="warning">Mensagem</span></p>
					</fieldset>
					
				</form>
				
				<p><h3>EXCLUIR PROMOÇÕES</h3></p>
				<!-- form -->
				<script type="text/javascript" src="js/form-validation.js"></script>
				<form id="contactForm" action="deletePromo.php" method="post">
					<fieldset>
														
<label for="promo">Promoção</label>
<select id="promo" name="promo">
<?php
	include 'dbConnection.php';
	$query = mysqli_query($link,"SELECT *
									FROM produto P, loja L, promocao B
									WHERE B.Produto_idProduto = P.idProduto and P.idProduto and P.Loja_idLoja = L.idLoja and L.idLoja IN (SELECT idLoja
																																			FROM loja
																																			WHERE CNPJ = '".$logado."')");
	while ($aux = mysqli_fetch_array($query))
		echo '<option value="'.$aux['idPromocao'].'"> '.$aux['nome'];
	
?>						
</select>
					<p><input type="submit" value="Enviar" name="submit" id="submit" /> <span id="error" class="warning">Mensagem</span></p>
					</fieldset>
					
				</form>
				
				
				
				<!-- ENDS form -->				
				
    		</div>
    		<!-- ENDS page content-->
			
			
			
			</div><!-- ENDS WRAPPER -->
		</div>
		<!-- ENDS MAIN -->
		
		
		<!-- FOOTER -->
		<footer>
			<div class="wrapper cf">
			
				<!-- widgets -->
				<ul  class="widget-cols cf">
					<li class="first-col">
						
						<div class="widget-block">
							<h4>RECENT POSTS</h4>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
							<div class="recent-post cf">
								<a href="#" class="thumb"><img src="img/dummies/54x54.gif" alt="Post" /></a>
								<div class="post-head">
									<a href="#">Pellentesque habitant morbi senectus</a><span> March 12, 2011</span>
								</div>
							</div>
						</div>
					</li>
					
					<li class="second-col">
						
						<div class="widget-block">
							<h4>ABOUT</h4>
							<p>Folder it's completely free this means you don't have to pay anything <a href="http://luiszuno.com/blog/license" tar >read license</a>.</p> 
							<p>Visit <a href="http://templatecreme.com/" >Template Creme</a> and find the most beautiful free templates up to date.</p>
						</div>
						
					</li>
					
					<li class="third-col">
						
						<div class="widget-block">
							<div id="tweets" class="footer-col tweet">
		         				<h4>TWITTER WIDGET</h4>
		         			</div>
		         		</div>
		         		
					</li>
					
					<li class="fourth-col">
						
						<div class="widget-block">
							<h4>CATEGORIES</h4>
							<ul>
								<li class="cat-item"><a href="#" >Design</a></li>
								<li class="cat-item"><a href="#" >Photo</a></li>
								<li class="cat-item"><a href="#" >Art</a></li>
								<li class="cat-item"><a href="#" >Game</a></li>
								<li class="cat-item"><a href="#" >Film</a></li>
								<li class="cat-item"><a href="#" >TV</a></li>
							</ul>
						</div>
		         		
					</li>	
				</ul>
				<!-- ENDS widgets -->	
				
				
				<!-- bottom -->
				<div class="footer-bottom">
						<ul id="social-bar" class="cf sb">
							<li><a href="http://www.facebook.com"  title="Become a fan" class="facebook">Facebbok</a></li>
							<li><a href="http://www.twitter.com" title="Follow my tweets" class="twitter"></a></li>
							<li><a href="http://plus.google.com" title="Enter my circles" class="plus"></a></li>
						</ul>
				</div>	
				<!-- ENDS bottom -->
			
			</div>
		</footer>
		<!-- ENDS FOOTER -->
		
		<!-- Start google map -->
		<script>initialize();</script>
	
	</body>
	
	
	
</html>