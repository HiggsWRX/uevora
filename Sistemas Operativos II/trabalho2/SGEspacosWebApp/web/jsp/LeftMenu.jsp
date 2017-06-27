<%@page language="java" contentType="text/html"%>

<%@page import="java.util.LinkedList"%>
<%@page import="java.util.Enumeration"%>

<% String base = (String) application.getAttribute("base");%>

<jsp:useBean id="dataManager" scope="application"
             class="eshop.model.DataManager"/>
<div class="menu"> 
    <div class="box" >
        <div class="title">Menu</div>
        <a class="link" href="<%=base%>?action=listSpaces">Espaços do Clube</a><br>
        <a class="link" href="<%=base%>?action=verifyAvailability">Verificar disponibilidade</a><br>
        <a class="link" href="<%=base%>?action=makeReservation">Fazer uma reserva</a><br>
        <a class="link" href="<%=base%>?action=listReservations">Listar reservas</a><br>
    </div>
</div>