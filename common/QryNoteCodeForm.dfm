inherited frmQryNoteCode: TfrmQryNoteCode
  Caption = #26597#35810#21333#21495
  ClientHeight = 155
  ClientWidth = 286
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  OnShow = FormShow
  ExplicitWidth = 292
  ExplicitHeight = 183
  PixelsPerInch = 96
  TextHeight = 17
  inherited Panel2: TPanel
    Width = 286
    Height = 155
    Align = alClient
    Color = 16180174
    ParentBackground = False
    ExplicitTop = 8
    ExplicitWidth = 513
    ExplicitHeight = 385
    DesignSize = (
      286
      155)
    object lbl1: TRzLabel [0]
      Left = 13
      Top = 27
      Width = 48
      Height = 17
      Caption = #36873#25321#26085#26399
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl2: TRzLabel [1]
      Left = 13
      Top = 58
      Width = 48
      Height = 17
      Caption = #24215'      '#21495
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl3: TRzLabel [2]
      Left = 13
      Top = 87
      Width = 48
      Height = 17
      Caption = #21333'      '#21495
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    inherited btnOk: TRzButton
      Left = 93
      Top = 122
      ExplicitLeft = 87
      ExplicitTop = 128
    end
    inherited btnCancel: TRzButton
      Left = 184
      Top = 122
      ExplicitLeft = 178
      ExplicitTop = 128
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 86
      Top = 24
      Width = 171
      Height = 25
      EditType = etDate
      TabOrder = 2
      OnChange = dtedtDateChange
    end
    object cbb1: TRzComboBox
      Left = 86
      Top = 54
      Width = 171
      Height = 25
      Enabled = False
      ItemHeight = 17
      TabOrder = 3
    end
    object spedtID: TRzSpinEdit
      Left = 86
      Top = 84
      Width = 51
      Height = 25
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 4
      OnChange = spedtIDChange
    end
    object edtCode: TRzEdit
      Left = 136
      Top = 84
      Width = 121
      Height = 25
      Color = clInfoBk
      ReadOnly = True
      TabOrder = 5
    end
  end
end
