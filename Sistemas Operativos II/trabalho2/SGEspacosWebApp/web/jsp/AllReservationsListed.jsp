<%@page import="eshop.beans.Reserva"%>
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
        <title>Espacos Disponiveis</title>
        <link rel="stylesheet" href="css/eshop.css" type="text/css"/>
    </head>
    <body>
        <jsp:include page="TopMenu.jsp" flush="true"/>
        <jsp:include page="LeftMenu.jsp" flush="true"/>
        <div class="content">
            <%
                String codEsp = request.getParameter("space");
            %>
            <h2><%=codEsp%> - Espacos Reservados</h2>
            <table>
                <tr>
                    <th>Nome Responsavel</th>
                    <th>Inicio da Reserva</th>
                    <th>Fim da Reserva</th>
                </tr>

                <%
                    try {
                        Vector<Reserva> reservas = dataManager.getReservationList(codEsp);
                        if (reservas != null) {
                            for (Reserva r : reservas) {
                                out.println(
                                        "<tr>"
                                        + "<td>" + r.getResName() + "</td>"
                                        + "<td>" + r.getResStartT() + "</td>"
                                        + "<td>" + r.getResEndT() + "</td>"
                                        + "</tr>");
                            }
                        } else {
                %><tr><td>No</td><td>Reservations</td><td>Found</td></tr> <%
                                }
                            } catch (Exception e) {
                %><p class="error">Invalid book identifier!</p><%
                    }
                %>
            </table>
        </div>  <!-- final da seccao de content -->
    </body>
</html>
