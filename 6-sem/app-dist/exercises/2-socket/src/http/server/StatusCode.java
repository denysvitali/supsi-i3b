package http.server;

public enum StatusCode {
	OK(200, "OK"),
	NOT_FOUND(404, "Not Found");

	private int code;
	private String name;

	StatusCode(int code, String s){
		this.code = code;
		this.name = s;
	}

	public int getCode() {
		return code;
	}

	public String getName() {
		return name;
	}
}
