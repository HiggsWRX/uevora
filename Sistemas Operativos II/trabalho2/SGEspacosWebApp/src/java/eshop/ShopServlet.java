package eshop;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import eshop.model.DataManager;
import javax.servlet.http.HttpServlet;

/**
 *
 * @author jsaias
 */
public class ShopServlet extends HttpServlet {

    public ShopServlet() {
        super();
    }

    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        System.out.println("*** initializing controller servlet.");  // fica nos logs
        System.out.println("Aplicacao - CONTEXT Path: " + getServletContext().getContextPath());

        ServletContext context = config.getServletContext();
        // visiveis em toda a aplicação (contexto de execução das Servlets)
        // 2 atributos com configurações recebidas de web.xml
        context.setAttribute("base", config.getInitParameter("base"));
        context.setAttribute("imageURL", config.getInitParameter("imageURL"));

        // **********
        // PostgreSQL:
        context.setAttribute("dbURL", config.getInitParameter("PostgreSQL_dbURL"));
        context.setAttribute("dbName", config.getInitParameter("PostgreSQL_dbName"));
        context.setAttribute("dbUser", config.getInitParameter("PostgreSQL_dbUser"));
        context.setAttribute("dbPassword", config.getInitParameter("PostgreSQL_dbPassword"));
        // ***********************************************

        DataManager dataManager = new DataManager(context);
        // atributo com o objeto que gere o acesso aos dados (partilhado pelos componentes web)
        context.setAttribute("dataManager", dataManager);
    }

    @Override
    public void destroy() {
        ServletContext context = this.getServletContext();
        DataManager dataManager = (DataManager) context.getAttribute("dataManager");
        if (dataManager != null) {
            try {
                /**
                 * terminar a ligacao 'a BD de modo seguro:
                 */
                dataManager.finish();
            } catch (Exception e) {
                System.err.println("PROBLEMA AO FINALIZAR: " + e.getMessage());
            }
        }
    }

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String base = "/jsp/";
        String url = base + "index.jsp";
        String action = request.getParameter("action");
        if (action != null) {
            if (action.equals("spaceform")) {
                url = base + "AllReservationsListed.jsp";
            } else if (action.equals("listReservations")) {
                url = base + "AllReservations.jsp";
            } else if (action.equals("listSpaces")) {
                url = base + "Spaces.jsp";
            } else if (action.equals("verifyAvailability")) {
                url = base + "Availability.jsp";
            } else if (action.equals("availform")) {
                url = base + "AvailabilityChecked.jsp";
            } else if (action.equals("makeReservation")) {
                url = base + "MakeReservation.jsp";
            } else if (action.equals("resform")) {
                url = base + "ReservationResult.jsp";
            }
        }

        // encaminhar o processamento para o Componente Web adequado
        RequestDispatcher requestDispatcher
                = getServletContext().getRequestDispatcher(url);
        requestDispatcher.forward(request, response);
    }

    // **********************************
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }

}
