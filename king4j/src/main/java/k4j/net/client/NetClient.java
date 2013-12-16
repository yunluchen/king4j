package k4j.net.client;

/**
 * Created by tom on 12/16/13.
 */
public interface NetClient {

    void setHandler(NetClientHandler netClientHandler);

    void send(String value);

}
