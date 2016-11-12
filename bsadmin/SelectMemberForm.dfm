inherited frmSelectMember: TfrmSelectMember
  Caption = #36873#25321#20250#21592
  ClientHeight = 266
  ClientWidth = 260
  Font.Charset = ANSI_CHARSET
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  ExplicitWidth = 266
  ExplicitHeight = 294
  PixelsPerInch = 96
  TextHeight = 17
  inherited Panel2: TPanel
    Width = 260
    Height = 266
    Align = alClient
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    ExplicitWidth = 260
    ExplicitHeight = 266
    object lbl1: TRzLabel [0]
      Left = 8
      Top = 11
      Width = 56
      Height = 20
      Caption = #20250#21592#21345#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine1: TRzLine [1]
      Left = 1
      Top = 70
      Width = 260
      Height = 20
    end
    object lbl2: TRzLabel [2]
      Left = 8
      Top = 99
      Width = 56
      Height = 20
      Caption = #20250#21592#21345#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl4: TRzLabel [3]
      Left = 8
      Top = 130
      Width = 56
      Height = 20
      Caption = #20250#21592#21517#31216
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl5: TRzLabel [4]
      Left = 8
      Top = 160
      Width = 56
      Height = 20
      Caption = #20248#24800#25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl6: TRzLabel [5]
      Left = 8
      Top = 190
      Width = 56
      Height = 20
      Caption = #21345#20869#20313#39069
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label1: TLabel [6]
      Left = 22
      Top = 44
      Width = 42
      Height = 20
      Caption = #39564#35777#30721
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    inherited btnOk: TRzButton
      Left = 96
      Top = 231
      Caption = #30830#35748'[Ent]'
      Font.Charset = ANSI_CHARSET
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      ParentFont = False
      TabOrder = 1
      ExplicitLeft = 96
      ExplicitTop = 231
    end
    inherited btnCancel: TRzButton
      Left = 177
      Top = 231
      Caption = #21462#28040'[Esc]'
      Font.Charset = ANSI_CHARSET
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      ParentFont = False
      TabOrder = 2
      OnClick = btnCancelClick
      ExplicitLeft = 177
      ExplicitTop = 231
    end
    object edtMember: TRzEdit
      Left = 74
      Top = 8
      Width = 160
      Height = 26
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      MaxLength = 13
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnKeyPress = edtMemberKeyPress
    end
    object dbedtCardSN: TRzDBEdit
      Left = 74
      Top = 97
      Width = 160
      Height = 26
      DataSource = dsrc1
      DataField = 'CardSN'
      ReadOnly = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      FocusColor = clInfoBk
      FrameColor = clMedGray
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 3
      OnKeyPress = dbedtCardSNKeyPress
    end
    object dbedtName: TRzDBEdit
      Left = 74
      Top = 128
      Width = 160
      Height = 26
      DataSource = dsrc1
      DataField = 'Name'
      ReadOnly = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      FocusColor = clInfoBk
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 4
    end
    object dbnbedtDiscount: TRzDBNumericEdit
      Left = 74
      Top = 158
      Width = 160
      Height = 26
      DataSource = dsrc1
      DataField = 'Discount'
      ReadOnly = True
      Alignment = taLeftJustify
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 5
      DisplayFormat = '0.00'
    end
    object dbnbedtBalance: TRzDBNumericEdit
      Left = 74
      Top = 188
      Width = 160
      Height = 26
      DataSource = dsrc1
      DataField = 'Balance'
      ReadOnly = True
      Alignment = taLeftJustify
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 6
      DisplayFormat = '##0.00;-##0.00'
    end
    object edpassword: TEdit
      Left = 74
      Top = 41
      Width = 160
      Height = 26
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 7
      Visible = False
      OnKeyPress = edpasswordKeyPress
    end
  end
  object dsetMember: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select Name,CardSN,Balance,Discount '#13#10'from CUST_MemberInfo left ' +
      'join CUST_MemberType on CUST_MemberInfo.MemberType=CUST_MemberTy' +
      'pe.IDType'
    Parameters = <>
    Left = 16
    Top = 206
  end
  object dsrc1: TDataSource
    DataSet = dsetMember
    Left = 40
    Top = 232
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 240
    Top = 96
  end
end
