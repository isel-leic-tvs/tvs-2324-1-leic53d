- Choose a location for the file useless.sh (e.g /home/isel/useless.sh )
- Make it an executable script with: chmod 755 useless.sh
- Edit the file useless.service and configure ExecStart to refer the location of useless.sh
- Place the file useless.service in /etc/systemd/system/useless.service
- Reload systemd configuration files with: sudo systemctl daemon-reload

- You can now start / stop / check status for the useless service:
  1. systemctl status useless.service      (service is inactive)
  2. sudo systemctl start useless.service  (starts the service)
  3. systemctl status useless.service      (service is running)
	4. wait a few seconds
  5. systemctl status useless.service      (check log lines at the bottom)
	6. sudo journalctl -u useless.service    (read the full log for this service)
	   - up / down arrows to move ; q to exit
	7. sudo systemctl stop useless.service   (stops the service)
  8. systemctl status useless.service      (service is inactive)
