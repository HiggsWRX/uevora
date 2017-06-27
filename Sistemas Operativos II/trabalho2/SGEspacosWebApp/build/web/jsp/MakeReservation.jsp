<%@page import="java.util.Vector"%>
<%@page language="java" contentType="text/html"%>
<%@page import="eshop.beans.Espaco"%>

<%-- Isto é um comentário JSP... --%>
<%-- a indicacao abaixo disponibiliza a variável dataManager, para acesso aos dados --%>
<jsp:useBean id="dataManager" scope="application" class="eshop.model.DataManager"/>

<%
    String base = (String) application.getAttribute("base");
    String imageURL = (String) application.getAttribute("imageURL");
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <title>Fazer uma reserva</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <h2>Fazer a reserva de um espaço</h2>
            <form style="border: 0px solid; padding: 0; margin: 0;">
                <input type="hidden" name="action" value="resform"/>
                <p>Nome do Responsavel</p>
                <input type="text" name="nomeresp" required><br>
                <p>Telefone do Responsavel</p>
                <input type="text" name="tlfresp" required><br>
                <p>Numero de pessoas</p>
                <input type="number" name="numpessoas" min="1" max="30" required><br>
                <p>Espaco a reservar</p>
                <input type="radio" name="space" value="FUT01" required/>Futsal
                <input type="radio" name="space" value="TEN01"/>Tenis
                <input type="radio" name="space" value="PAD01"/>Padel<br>
                <p>Dia a reservar</p>
                <input type="date" name="date" required/><br>
                <p>Hora de Inicio</p>
                <input type="time" name="timestart" required/><br>
                <p>Duracao da reserva</p>
                <input type="number" name="duration" min="0" max="24" required/><br><br>
                <input id="submit" type="submit" value="Reservar"/>
            </form>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
