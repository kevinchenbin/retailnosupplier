inherited frmQryProcureNote1: TfrmQryProcureNote1
  Caption = #30465#20195#37319#36141#26597#35810
  PixelsPerInch = 96
  TextHeight = 13
  inherited pgcntrlResult: TRzPageControl
    ExplicitTop = 173
    FixedDimension = 23
    inherited tbshtByNtHeader: TRzTabSheet
      inherited dbgrdByNtHeader: TDBGridEh
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 100
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'Remarks'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 150
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'Operatorname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25805#20316#21592
            Width = 50
          end>
      end
    end
    inherited tbshtByNote: TRzTabSheet
      inherited dbgrdByNote: TDBGridEh
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footer.FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23458#25143
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'ISBN'
            Footers = <>
            Title.Alignment = taCenter
            Visible = False
            Width = 100
          end
          item
            EditButtons = <>
            FieldName = 'BookName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20070#21517
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'UserDefCode'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #33258#32534#30721
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'Price'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23450#20215
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'Author'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20316#32773
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#21035
            Visible = False
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 100
          end
          item
            EditButtons = <>
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Visible = False
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
            Visible = False
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'shanqicaigou'
            Footer.FieldName = 'shanqicaigou'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #19978#26399#37319#36141
          end
          item
            EditButtons = <>
            FieldName = 'benqiorder'
            Footer.FieldName = 'benqiorder'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26412#26399#25910#35746
          end
          item
            EditButtons = <>
            FieldName = 'benqidaixiao'
            Footer.FieldName = 'benqidaixiao'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26412#26399#20195#38144
          end
          item
            EditButtons = <>
            FieldName = 'benqicaigou'
            Footer.FieldName = 'benqicaigou'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26412#26399#37319#36141
          end
          item
            EditButtons = <>
            FieldName = 'orderdiscount'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25910#35746#25240#25187
          end
          item
            EditButtons = <>
            FieldName = 'fahuofashi'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21457#36135#26041#24335
            Width = 60
          end
          item
            EditButtons = <>
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25240#25187
            Visible = False
            Width = 45
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'remarks'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 190
          end
          item
            EditButtons = <>
            FieldName = 'ordercode'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25910#35746#21333#21495
            Visible = False
            Width = 71
          end
          item
            EditButtons = <>
            FieldName = 'clientname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #27969#21521
            Visible = False
            Width = 78
          end
          item
            EditButtons = <>
            FieldName = 'yifa'
            Footer.FieldName = 'yifa'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21457
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'weifa'
            Footer.FieldName = 'weifa'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21457
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'PressDate'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20986#29256#26085#26399
            Visible = False
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #31867#21035
            Visible = False
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'bookcatalogid'
            Footers = <>
            Visible = False
          end>
      end
    end
    inherited tbshtByCustomer: TRzTabSheet
      inherited dbgrdByCustomer: TDBGridEh
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 180
          end>
      end
    end
    inherited tbshtByBktype: TRzTabSheet
      inherited dbgrdByBktype: TDBGridEh
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #31867#21035
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 180
          end>
      end
    end
    inherited tbshtByPress: TRzTabSheet
      inherited dbgrdByPress: TDBGridEh
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'pressinfoabbname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#21035
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 180
          end>
      end
    end
  end
  inherited rztlbr1: TRzToolbar
    ToolbarControls = (
      tlbtnQry
      tlbtnExport
      BtnAlignBottom
      tlbtnExit)
  end
  inherited ImageList1: TImageList
    Bitmap = {
      494C010108000A00C40010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      990000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E500CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B200CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B200CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E500CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E50000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E5000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FDFFFDFFFFFFFFFFE0FFE8FFFFFFFFFF
      801FA05F80038003001F803F80038003001F001F80038003000F000F80038003
      000F000F80038003000F000FFFFFFFFF00010001BFFBBFFB01010001FFFFFFFF
      01010001BFFBBFFB000F000FFFFFFFFF008F000FBFFBBFFB00AF002FFFFFFFFF
      803F803FAAABAAABE1FFE1FFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FFFFDFFFDF
      83FF83FFFFCFFFCF81FF81FFE007E007C0FFC0FFFFCFFFCFE003E003FFDFFFDF
      F001F001FFFFFFFFF800F80001800180F800F80001807D80F800F80001807D80
      F800F80001807D80F800F80001807D80F800F80001806180F800F80003816381
      FC01FC0107836783FE03FE030F870F8700000000000000000000000000000000
      000000000000}
  end
end
