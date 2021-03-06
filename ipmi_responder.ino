
void respondToIPMI(const char *data, word len, byte *srcip, word port) {
  Serial.println("Got an IPMI packet");

  Serial.print("Function code: ");
  Serial.println(data[0], HEX);

  int auth_type = data[4];
  int cmd_offset = 0;
  switch (data[0]) {
    case IPMI_NETFN_APP:
      Serial.println("  Handling APP stuff");
      Serial.print("  Command: ");

      if (auth_type == 0x00) {
        // None
        cmd_offset = 19;
      } else if (auth_type == 0x02) {
        // MD5
        cmd_offset = 19 + 16;
      }

      Serial.println(data[cmd_offset], HEX);
      switch (data[cmd_offset]) {
        case IPMI_CMD_GET_CHAN_AUTH_CAPA: {
            return ipmi_app_auth_capa(srcip, port);
          }
        case IPMI_CMD_GET_SESS_CHALLENGE: {
            return ipmi_app_get_sess_challenge(srcip, port);
          }
        case IPMI_CMD_ACTIVE_SESS: {
            return ipmi_app_active_sess(srcip, port);
          }
        case IPMI_CMD_SET_SES_PRIV_LEVEL: {
            return ipmi_cmd_set_ses_priv_level(srcip, port);
          }
        case IPMI_CMD_GET_DEVICE_ID: {
            return ipmi_cmd_get_device_id(srcip, port);
          }
        case IPMI_CMD_CLOSE_SESSION: {
            return ipmi_cmd_close_session(srcip, port);
          }
        default: {
            return ipmi_cmd_uknown(srcip, port);
          }
      }
      return;
    default: {
        Serial.println("Unknown function code");
      }
  }
}

