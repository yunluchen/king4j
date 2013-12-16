package k4j.net.server;

import k4j.net.server.inner.NetServerImpl;

/**
 * Created by tom on 12/16/13.
 */
public class NetServerFactory {

    public static NetServer createNetServer(int serverPort) {
        return new NetServerImpl(serverPort);
    }

}
