inherited frmMixedRecMoney: TfrmMixedRecMoney
  Caption = #28151#21512#25910#27454
  ClientHeight = 393
  ClientWidth = 279
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  ExplicitWidth = 285
  ExplicitHeight = 421
  PixelsPerInch = 96
  TextHeight = 17
  object RzLabel1: TRzLabel [0]
    Left = 8
    Top = 11
    Width = 48
    Height = 17
    Caption = #24212#25910#37329#39069
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  inherited Panel2: TPanel
    Width = 279
    Height = 393
    Align = alClient
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    ExplicitWidth = 279
    ExplicitHeight = 393
    object Label1: TLabel [0]
      Left = 34
      Top = 19
      Width = 56
      Height = 19
      Caption = #24212#25910#37329#39069
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzLabel2: TRzLabel [1]
      Left = 27
      Top = 133
      Width = 63
      Height = 19
      Caption = #20648#20540#21345'(&A)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel3: TRzLabel [2]
      Left = 42
      Top = 306
      Width = 48
      Height = 19
      Caption = #29616#37329'(&X)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TRzLabel [3]
      Left = 20
      Top = 99
      Width = 70
      Height = 19
      Caption = #20648#20540#21345#20313#39069
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine1: TRzLine [4]
      Left = 8
      Top = 70
      Width = 257
      Height = 20
    end
    object RzLabel4: TRzLabel [5]
      Left = 30
      Top = 167
      Width = 60
      Height = 19
      Caption = #20248#24800#21048'(&S)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel [6]
      Left = 29
      Top = 202
      Width = 61
      Height = 19
      Caption = #38134#34892#21345'(&Z)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel6: TRzLabel [7]
      Left = 29
      Top = 240
      Width = 62
      Height = 19
      Caption = #25903#20184#23453'(&B)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel7: TRzLabel [8]
      Left = 37
      Top = 273
      Width = 53
      Height = 19
      Caption = #24494#20449'(&W)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label2: TLabel [9]
      Left = 34
      Top = 48
      Width = 56
      Height = 19
      Caption = #23454#25910#37329#39069
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    inherited btnOk: TRzButton
      Left = 91
      Top = 340
      Width = 76
      Height = 35
      Caption = #30830#35748'(Ent)'
      Color = 16180174
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitLeft = 91
      ExplicitTop = 340
      ExplicitWidth = 76
      ExplicitHeight = 35
    end
    inherited btnCancel: TRzButton
      Left = 174
      Top = 340
      Width = 76
      Height = 35
      Caption = #21462#28040'(Esc)'
      Color = 16180174
      Font.Charset = ANSI_CHARSET
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      ExplicitLeft = 174
      ExplicitTop = 340
      ExplicitWidth = 76
      ExplicitHeight = 35
    end
    object numedtCard: TRzNumericEdit
      Left = 110
      Top = 131
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnExit = numedtCardExit
      OnKeyPress = numedtCardKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object numedtCash: TRzNumericEdit
      Left = 110
      Top = 304
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = numedtCashClick
      OnExit = numedtCardExit
      OnKeyPress = numedtCashKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object numedtRemain: TRzNumericEdit
      Left = 110
      Top = 97
      Width = 140
      Height = 25
      Color = clInfoBk
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
      OnKeyPress = numedtCardKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object numedtyouhui: TRzNumericEdit
      Left = 110
      Top = 165
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnExit = numedtCardExit
      OnKeyPress = numedtyouhuiKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object numedtposcard: TRzNumericEdit
      Left = 110
      Top = 200
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnExit = numedtCardExit
      OnKeyPress = numedtposcardKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object zifubao: TRzNumericEdit
      Left = 110
      Top = 238
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      OnExit = numedtCardExit
      OnKeyPress = zifubaoKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object weixin: TRzNumericEdit
      Left = 110
      Top = 269
      Width = 140
      Height = 25
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnExit = numedtCardExit
      OnKeyPress = weixinKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
    object ssje: TRzNumericEdit
      Left = 110
      Top = 48
      Width = 140
      Height = 25
      Color = clInfoBk
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 9
      OnExit = numedtCardExit
      OnKeyPress = numedtCardKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.0;'
    end
  end
  object numedtMustRecMoney: TRzNumericEdit
    Left = 110
    Top = 17
    Width = 140
    Height = 25
    Color = clInfoBk
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = #24494#36719#38597#40657
    Font.Style = [fsBold]
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ParentCtl3D = False
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    DisplayFormat = '###,##0.0'
  end
end
