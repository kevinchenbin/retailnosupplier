inherited frmSetNotes: TfrmSetNotes
  Caption = #32479#19968
  ClientHeight = 253
  ClientWidth = 208
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  OnShow = FormShow
  ExplicitWidth = 214
  ExplicitHeight = 281
  PixelsPerInch = 96
  TextHeight = 17
  inherited Panel2: TPanel
    Width = 208
    Height = 301
    Align = alTop
    ParentBackground = False
    ExplicitWidth = 208
    ExplicitHeight = 301
    inherited btnOk: TRzButton
      Left = 17
      Top = 212
      ExplicitLeft = 17
      ExplicitTop = 212
    end
    inherited btnCancel: TRzButton
      Left = 115
      Top = 212
      ExplicitLeft = 115
      ExplicitTop = 212
    end
    object grpbx1: TRzGroupBox
      Left = 9
      Top = 5
      Width = 193
      Height = 201
      Anchors = [akLeft, akTop, akRight, akBottom]
      BorderColor = clInactiveCaptionText
      Caption = #35774#32622#25968#37327#21644#25240#25187
      GradientColorStop = clInactiveCaptionText
      ParentColor = True
      TabOrder = 2
      object chckbxAmount: TRzCheckBox
        Left = 4
        Top = 21
        Width = 43
        Height = 19
        Caption = #25968#37327
        State = cbUnchecked
        TabOrder = 0
        OnClick = chckbxAmountClick
        OnKeyPress = chckbxAmountKeyPress
      end
      object chckbxDiscount: TRzCheckBox
        Left = 4
        Top = 50
        Width = 43
        Height = 19
        Caption = #25240#25187
        State = cbUnchecked
        TabOrder = 2
        OnClick = chckbxDiscountClick
        OnKeyPress = chckbxAmountKeyPress
      end
      object numedtDiscount: TRzNumericEdit
        Left = 79
        Top = 48
        Width = 102
        Height = 25
        TabOrder = 3
        OnChange = numedtDiscountChange
        OnKeyPress = numedtDiscountKeyPress
        BlankValue = 100.000000000000000000
        IntegersOnly = False
        Max = 100.000000000000000000
        DisplayFormat = '##0.00'#13#10
      end
      object numedtAmount: TRzNumericEdit
        Left = 79
        Top = 19
        Width = 102
        Height = 25
        TabOrder = 1
        OnChange = numedtAmountChange
        OnKeyPress = numedtAmountKeyPress
        DisplayFormat = '###,##0;'
      end
      object chpixiaodiscount: TCheckBox
        Left = 4
        Top = 78
        Width = 69
        Height = 17
        Caption = #25209#38144#25240#25187
        TabOrder = 4
        Visible = False
      end
      object edpixiaodiscount: TRzNumericEdit
        Left = 79
        Top = 76
        Width = 102
        Height = 25
        TabOrder = 5
        Visible = False
        OnChange = edpixiaodiscountChange
        OnKeyPress = edpixiaodiscountKeyPress
        Value = 100.000000000000000000
        DisplayFormat = '##0.00'
      end
      object chlsdiscount: TCheckBox
        Left = 4
        Top = 107
        Width = 69
        Height = 17
        Caption = #38646#21806#25240#25187
        TabOrder = 6
        Visible = False
      end
      object edlsdiscount: TRzNumericEdit
        Left = 79
        Top = 105
        Width = 102
        Height = 25
        TabOrder = 7
        Visible = False
        OnChange = edlsdiscountChange
        OnKeyPress = edlsdiscountKeyPress
        Value = 100.000000000000000000
        DisplayFormat = '##0.00'
      end
      object huiyuancheck: TCheckBox
        Left = 4
        Top = 136
        Width = 69
        Height = 25
        Caption = #20250#21592#25240#25187
        TabOrder = 8
      end
      object zdlingkoucheck: TCheckBox
        Left = 4
        Top = 167
        Width = 69
        Height = 17
        Caption = #26368#20302#38646#25187
        TabOrder = 9
      end
      object huiyuandiscount: TRzNumericEdit
        Left = 79
        Top = 136
        Width = 102
        Height = 25
        TabOrder = 10
        OnChange = huiyuandiscountChange
        Value = 100.000000000000000000
        DisplayFormat = '##0.00'
      end
      object lingkoudiscount: TRzNumericEdit
        Left = 79
        Top = 167
        Width = 102
        Height = 25
        TabOrder = 11
        OnChange = lingkoudiscountChange
        Value = 100.000000000000000000
        DisplayFormat = '##0.00'
      end
    end
  end
end
