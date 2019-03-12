package it.denv.supsi.i3b.appdist.exercises;

import java.io.IOException;
import java.net.ConnectException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpHeaders;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private static String BASE_URL = "http://www.supsi.ch";

    public static void main(String[] args) throws IOException, InterruptedException, URISyntaxException {
        HttpClient client = HttpClient.newBuilder()
                .followRedirects(HttpClient.Redirect.ALWAYS)
                .build();
        HttpRequest req = HttpRequest.newBuilder().GET()
                .uri(new URI(BASE_URL + "/home.html"))
                .build();
        HttpResponse<String> resp = client.send(req,
                HttpResponse.BodyHandlers.ofString());

        HttpHeaders headers = resp.headers();

        System.out.println(headers.map());

        Pattern p = Pattern.compile("src=\"(.*?)\"", Pattern.CASE_INSENSITIVE);
        Matcher m = p.matcher(resp.body());

        ArrayList<String> urls = new ArrayList<>();

        while(m.find()){
            urls.add(m.group(1));
        }

        HashMap<String, Integer> sizes = new HashMap<>();

        for(String url: urls){
            if(url.startsWith("//")){
                url = url.replaceFirst("\\/\\/", "http://");
            } else if(url.startsWith("/")){
                url = url.replaceFirst("/", BASE_URL + "/");
            }
            HttpRequest m_req = HttpRequest.newBuilder()
                    .GET()
                    .uri(new URI(url))
            .build();

            System.out.println("Url is " + url);

            HttpResponse<Void> m_resp;
            try {
                 m_resp = client.send(m_req,
                         HttpResponse.BodyHandlers.discarding());

            } catch(ConnectException ex){
                System.out.println("Unable to connect to " + url);
                continue;
            }
            String contentLength = m_resp.headers().map()
                    .keySet()
                    .stream()
                    .filter(a -> a.toLowerCase().equals("content-length")).findAny().orElse(null);

            if(contentLength != null) {
                int size = Integer.valueOf(m_resp.headers().map()
                        .get(contentLength).get(0));
                sizes.put(url, size);
            } else {
                System.out.println("Content-Length unavailable for " + url);
            }
        }

        int overhead = urls.size()*850 + sizes.values()
                .stream()
                .reduce(Integer::sum)
                .orElse(0);

        System.out.println("Requests: " + urls.size());
        System.out.println("Overhead: " + overhead * 1.0 / 1024 + "kB");
        System.out.println("Sizes: " + sizes);
    }
}
