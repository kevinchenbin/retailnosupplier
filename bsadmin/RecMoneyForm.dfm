inherited frmRecMoney: TfrmRecMoney
  Caption = #29616#22330#32467#27454
  ClientHeight = 215
  ClientWidth = 243
  Color = clInactiveCaptionText
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  OnShow = FormShow
  ExplicitWidth = 249
  ExplicitHeight = 243
  PixelsPerInch = 96
  TextHeight = 17
  inherited Panel2: TPanel
    Width = 243
    Height = 215
    Align = alClient
    ParentBackground = False
    ExplicitWidth = 243
    ExplicitHeight = 215
    inherited btnOk: TRzButton
      Left = 66
      Top = 178
      ExplicitLeft = 66
      ExplicitTop = 178
    end
    inherited btnCancel: TRzButton
      Left = 147
      Top = 178
      ExplicitLeft = 147
      ExplicitTop = 178
    end
    object grpbx1: TRzGroupBox
      Left = 16
      Top = 0
      Width = 214
      Height = 172
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = 16180174
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 2
      object lbl1: TRzLabel
        Left = 8
        Top = 56
        Width = 64
        Height = 22
        Caption = #24050#32467#37329#39069
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl2: TRzLabel
        Left = 8
        Top = 136
        Width = 64
        Height = 22
        Caption = #29616#22330#20184#27454
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl3: TRzLabel
        Left = 8
        Top = 96
        Width = 64
        Height = 22
        Caption = #26410#32467#37329#39069
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel1: TRzLabel
        Left = 8
        Top = 16
        Width = 64
        Height = 22
        Caption = #24212#20184#37329#39069
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object numedtChecked: TRzNumericEdit
        Left = 78
        Top = 55
        Width = 115
        Height = 23
        Ctl3D = False
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
      object numedtReceive: TRzNumericEdit
        Left = 78
        Top = 135
        Width = 115
        Height = 23
        BiDiMode = bdLeftToRight
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentBiDiMode = False
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 0
        OnKeyPress = numedtReceiveKeyPress
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
      object numedtUnchecked: TRzNumericEdit
        Left = 78
        Top = 95
        Width = 115
        Height = 23
        Ctl3D = False
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
      object numedtshoud: TRzNumericEdit
        Left = 78
        Top = 15
        Width = 115
        Height = 23
        Ctl3D = False
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
    end
  end
end
