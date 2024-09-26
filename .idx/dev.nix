{ pkgs, ... }: {
  channel = "stable-23.11";

  packages = [ pkgs.python311 ];
  
  idx = {
    workspace = {
      onCreate = {
        pip-install = "python3 -m venv venv && source venv/bin/activate && pip install -r requirements.txt";
      };

      onStart = {
        preview = "cd ui && python3 -m http.server";
      };
    };
  };
}
