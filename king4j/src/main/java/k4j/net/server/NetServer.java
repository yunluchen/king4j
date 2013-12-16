package k4j.net.server;

/**
 * Created by tom on 12/16/13.
 */
public interface NetServer {

    void setHandler(NetServerHandler netServerHandler);

    void service();

    void stop();

}
